#include "TetrisGame.h"

// Define static constants
const int TetrisGame::BLOCK_WIDTH = 32;
const int TetrisGame::BLOCK_HEIGHT = 32;
const double TetrisGame::MAX_SECONDS_PER_TICK = 0.75;
const double TetrisGame::MIN_SECONDS_PER_TICK = 0.20;

// My Constants
const int POINTS_PER_LINE_CLEARED = 100;
const int VOLUME_INCREMENT = 10;
const float VOLUME_INITIAL = 50.0f;
const int NUM_SHAPES = 7;

// PUBLIC METHODS

/// @brief Constructor for TetrisGame.
/// @param window The SFML render window.
/// @param blockSprite The SFML sprite for blocks.
/// @param gameboardOffset The offset of the gameboard.
/// @param nextShapeOffset The offset of the next shape.
TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset)
    : window(window), 
      blockSprite(blockSprite), 
      gameboardOffset(gameboardOffset), 
      nextShapeOffset(nextShapeOffset),
      score(0),
      secondsSinceLastTick(0.0),
      shapePlacedSinceLastGameLoop(false),
      secondsPerTick(MAX_SECONDS_PER_TICK) {
    
    srand(time(nullptr));

    if (!scoreFont.loadFromFile("fonts/RedOctober.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    } else {
        std::cout << "Font loaded successfully" << std::endl;
        scoreText.setFont(scoreFont);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(425, 325);
    }

    if (!backgroundMusic.openFromFile("audio/Tetromino-Flow.ogg")) {
        std::cerr << "Failed to load background music" << std::endl;
    } else {
        std::cout << "Background music loaded successfully" << std::endl;
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(VOLUME_INITIAL);  // Set volume to 50% (0-100 range)
        backgroundMusic.play();
    } 

    reset();
}

/// @brief Draws the gameboard, current shape, next shape, and score.
void TetrisGame::draw() {
    drawGameboard();
    drawTetromino(currentShape, gameboardOffset);
    drawTetromino(nextShape, nextShapeOffset);
    window.draw(scoreText);
}

/// @brief Handles key presses.
/// @param event The SFML event.
void TetrisGame::onKeyPressed(const sf::Event& event) {
    switch (event.key.code) {
        case sf::Keyboard::Up:
            if (event.key.shift) {
                attemptRotateCounterClockwise(currentShape);
            } else if (event.key.control) {
                backgroundMusic.setVolume(backgroundMusic.getVolume() + VOLUME_INCREMENT);
            } else {
                attemptRotate(currentShape);
            }
            break;
        case sf::Keyboard::Left:
            attemptMove(currentShape, -1, 0);
            break;
        case sf::Keyboard::Right:
            attemptMove(currentShape, 1, 0);
            break;
        case sf::Keyboard::Down:
            if (event.key.control) {
                backgroundMusic.setVolume(backgroundMusic.getVolume() - VOLUME_INCREMENT);
            } else {
                attemptMove(currentShape, 0, 1);
            }
            break;
        case sf::Keyboard::Space:
            drop(currentShape);
            break;
        case sf::Keyboard::S:
            if (backgroundMusic.getStatus() == sf::Music::Playing) {
                backgroundMusic.pause();
            } else {
                backgroundMusic.play();
            }
            break;
    }
}

/// @brief Processes the game loop.
/// @param secondsSinceLastLoop The time since the last game loop.
void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
    secondsSinceLastTick += secondsSinceLastLoop;
    while (secondsSinceLastTick >= secondsPerTick) {
        tick();
        secondsSinceLastTick -= secondsPerTick;
    }

    // If a shape was placed since the last game loop, check for lines cleared
    if (shapePlacedSinceLastGameLoop) {
        int linesCleared = board.removeCompletedRows();
        
        switch (linesCleared) {
            case 1:
                score += 100;
                break;
            case 2:
                score += 300;
                break;
            case 3:
                score += 500;
                break;
            case 4:
                score += 800;
                break;
            default:
                break;
        }

        updateScoreDisplay();
        determineSecondsPerTick();

        // If the shape can't be spawned, reset the game
        if (!spawnNextShape()) {
            reset();
        }
        
        pickNextShape();
        shapePlacedSinceLastGameLoop = false;
    }
}

// PRIVATE METHODS

/// @brief Moves the current shape down one line if possible, otherwise locks it.
void TetrisGame::tick() {
    if (!attemptMove(currentShape, 0, 1)) { lock(currentShape); }
}

void TetrisGame::reset() {
    score = 0;
    updateScoreDisplay();
    board.empty();
    pickNextShape();
    spawnNextShape();
}

/// @brief Sets the next shape to a random shape.
void TetrisGame::pickNextShape() {
    int ranShape = rand() % NUM_SHAPES;
    nextShape.setShape(static_cast<TetShape>(ranShape));
}

/// @brief Sets the current shape to the next shape and sets its grid location to the spawn location.
/// @return True if the shape is legal, false otherwise.
bool TetrisGame::spawnNextShape() {
    currentShape = nextShape;
    currentShape.setGridLoc(board.getSpawnLoc());

    return isPositionLegal(currentShape);
}

/// @brief Attempts to rotate the shape clockwise.
/// @param shape The shape to rotate.
/// @return True if the rotation is legal, false otherwise.
bool TetrisGame::attemptRotate(GridTetromino& shape) {
    GridTetromino temp = shape;
    temp.rotateClockwise();
    
    if (isPositionLegal(temp)) {
        shape = temp;
        return true;
    }

    return false;
}

/// @brief Attempts to move the shape.
/// @param shape The shape to move.
/// @param xOffset The x offset to move the shape.
/// @param yOffset The y offset to move the shape.
/// @return True if the move is legal, false otherwise.
bool TetrisGame::attemptMove(GridTetromino& shape, int xOffset, int yOffset) {
    GridTetromino temp = shape;
    temp.move(xOffset, yOffset);
    if (isPositionLegal(temp)) {
        shape = temp;
        return true;
    }

    return false;
}

/// @brief Moves the shape down one line until it can't move anymore.
/// @param shape The shape to drop.
void TetrisGame::drop(GridTetromino& shape) {
    while(attemptMove(shape, 0, 1));
}

/// @brief Locks the shape on the board by setting the content of the shape's block locations to the shape's color.
/// @param shape The shape to lock.
void TetrisGame::lock(GridTetromino& shape) {
    std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
    for (const auto& loc : mappedLocs) {
        board.setContent(loc, static_cast<int>(shape.getColor()));
    }
    shapePlacedSinceLastGameLoop = true;
}

// GRAPHICS METHODS

/// @brief Draws a block.
/// @param topLeft The top left point of the block.
/// @param xOffset The x offset of the block.
/// @param yOffset The y offset of the block.
/// @param color The color of the block.
void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color) {
    blockSprite.setTextureRect(sf::IntRect(static_cast<int>(color) * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    
    float pixelX = topLeft.getX() + (xOffset * BLOCK_WIDTH);
    float pixelY = topLeft.getY() + (yOffset * BLOCK_HEIGHT);

    blockSprite.setPosition(pixelX, pixelY);
    window.draw(blockSprite);
}

/// @brief Draws the gameboard by iterating through each cell and drawing a block if it is not empty.
void TetrisGame::drawGameboard() {
    for (int row = 0; row < Gameboard::MAX_Y; row++) {
        for (int col = 0; col < Gameboard::MAX_X; col++) {
            int content = board.getContent(col, row);
            if (content != Gameboard::EMPTY_BLOCK) {
                drawBlock(gameboardOffset, col, row, static_cast<TetColor>(content));
            }
        }
    }
}

/// @brief Draws a tetromino.
/// @param tetromino The tetromino to draw.
/// @param topLeft The top left point of the tetromino.
void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft) {
    std::vector<Point> mappedLocs = tetromino.getBlockLocsMappedToGrid();
    Point gridLoc = tetromino.getGridLoc();
    
    for (const auto& loc : mappedLocs) {
        drawBlock(topLeft, loc.getX(), loc.getY(), tetromino.getColor());
    }
}

/// @brief Updates the score display by setting the string of the score text to the current score.
void TetrisGame::updateScoreDisplay() {
    scoreText.setString("Score: " + std::to_string(score));
}

// STATE & GAMEPLAY/LOGIC METHODS

/// @brief Checks if the shape is within the borders.
/// @param shape The shape to check.
/// @return True if the shape is within the borders, false otherwise.
bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {
    if (!isWithinBorders(shape)) {
        return false;
    }
    
    // Check if the locations are empty on the board
    std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
    for (const auto& loc : mappedLocs) {
        if (board.getContent(loc) != Gameboard::EMPTY_BLOCK) {
            return false;
        }
    }

    return true;
}


/// @brief Checks if the shape is within the borders.
/// @param shape The shape to check.
/// @return True if the shape is within the borders, false otherwise.
bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
    std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
    
    for (const Point& loc : mappedLocs) {
        // Check all borders: left, right, top, and bottom
        if (loc.getX() < 0 || loc.getX() >= Gameboard::MAX_X || 
            loc.getY() < 0 || loc.getY() >= Gameboard::MAX_Y) {

            return false;
        }
    }

    return true;
}

/// @brief Determines the seconds per tick based on the score by dividing the maximum seconds per tick by the score divided by 100 plus 1.
void TetrisGame::determineSecondsPerTick() {
    secondsPerTick = MAX_SECONDS_PER_TICK / (score / 100 + 1);
}

// MY OWN METHODS CUS IM COOL AS FUCK

/// @brief Attempts to rotate the shape counterclockwise.
/// @param shape The shape to rotate.
/// @return True if the rotation is legal, false otherwise.
bool TetrisGame::attemptRotateCounterClockwise(GridTetromino& shape) {
    // Create a temporary copy of the shape
    GridTetromino temp = shape;
    
    // Rotate the temporary shape
    temp.rotateCounterClockwise();
    
    // Check if the rotated position is legal
    if (isPositionLegal(temp)) {
        // If legal, apply the rotation to the actual shape
        shape = temp;

        return true;
    }
    
    return false;
}