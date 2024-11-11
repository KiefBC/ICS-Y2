#include "TetrisGame.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Define static constants
const int TetrisGame::BLOCK_WIDTH = 32;
const int TetrisGame::BLOCK_HEIGHT = 32;
const double TetrisGame::MAX_SECONDS_PER_TICK = 0.75;
const double TetrisGame::MIN_SECONDS_PER_TICK = 0.20;

// PUBLIC METHODS

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
    }

    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(450, 50);

    reset();
}

void TetrisGame::draw() {
    drawGameboard();
    drawTetromino(currentShape, gameboardOffset);
    drawTetromino(nextShape, nextShapeOffset);
    window.draw(scoreText);
}

void TetrisGame::onKeyPressed(const sf::Event& event) {
    switch (event.key.code) {
        case sf::Keyboard::Up:
            attemptRotate(currentShape);
            break;
        case sf::Keyboard::Left:
            attemptMove(currentShape, -1, 0);
            break;
        case sf::Keyboard::Right:
            attemptMove(currentShape, 1, 0);
            break;
        case sf::Keyboard::Down:
            attemptMove(currentShape, 0, 1);
            break;
        case sf::Keyboard::Space:
            drop(currentShape);
            break;
    }
}

void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
    secondsSinceLastTick += secondsSinceLastLoop;
    while (secondsSinceLastTick >= secondsPerTick) {
        tick();
        secondsSinceLastTick -= secondsPerTick;
    }

    // If a shape was placed since the last game loop, check for lines cleared
    if (shapePlacedSinceLastGameLoop) {
        // Remove any completed rows and update the score
        int linesCleared = board.removeCompletedRows();
        score += linesCleared * 100; // 100 points per line cleared
        updateScoreDisplay();

        // Adjust the tick rate based on the number of lines cleared
        determineSecondsPerTick();

        // If the shape can't be spawned, reset the game
        if (!spawnNextShape()) {
            reset();
        }

        // Pick the next shape
        pickNextShape();
        shapePlacedSinceLastGameLoop = false;
    }
}

// PRIVATE METHODS

void TetrisGame::tick() {
    attemptMove(currentShape, 0, 1);

    // If the shape can't be moved down, lock it in place
    if (!isPositionLegal(currentShape)) {
        lock(currentShape);
        shapePlacedSinceLastGameLoop = true;
    }
}

void TetrisGame::reset() {
    score = 0;
    updateScoreDisplay();
    board.empty();
    pickNextShape();
    spawnNextShape();
}

void TetrisGame::pickNextShape() {
    int ranShape = rand() % 7;
    nextShape.setShape(static_cast<TetShape>(ranShape));
    nextShape.setGridLoc(board.getSpawnLoc());
}

bool TetrisGame::spawnNextShape() {
    currentShape = nextShape;
    currentShape.setGridLoc(board.getSpawnLoc());
    return isPositionLegal(currentShape);
}

bool TetrisGame::attemptRotate(GridTetromino& shape) {
    GridTetromino temp = shape;
    temp.rotateClockwise();
    if (isPositionLegal(temp)) {
        shape = temp;
        return true;
    }
    return false;
}

bool TetrisGame::attemptMove(GridTetromino& shape, int xOffset, int yOffset) {
    GridTetromino temp = shape;
    temp.move(xOffset, yOffset);
    if (isPositionLegal(temp)) {
        shape = temp;
        return true;
    }
    return false;
}

void TetrisGame::drop(GridTetromino& shape) {
    while(attemptMove(shape, 0, 1));
}

void TetrisGame::lock(GridTetromino& shape) {
    // 1. Get the mapped locations of the shape
    std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();

    // 2. Set the content of the board at the mapped locations
    for (const auto& loc : mappedLocs) {
        board.setContent(loc, static_cast<int>(shape.getColor()));
    }

    // 3. Set the flag
    shapePlacedSinceLastGameLoop = true;
}

// GRAPHICS METHODS

void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color) {
    blockSprite.setTextureRect(sf::IntRect(static_cast<int>(color) * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    
    float pixelX = topLeft.getX() + (xOffset * BLOCK_WIDTH);
    float pixelY = topLeft.getY() + (yOffset * BLOCK_HEIGHT);

    blockSprite.setPosition(pixelX, pixelY);
    window.draw(blockSprite);
}

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

void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft) {
    std::vector<Point> mappedLocs = tetromino.getBlockLocsMappedToGrid();
    Point gridLoc = tetromino.getGridLoc();
    
    for (const auto& loc : mappedLocs) {
        drawBlock(topLeft, loc.getX(), loc.getY(), tetromino.getColor());
    }
}

void TetrisGame::updateScoreDisplay() {
    scoreText.setString("Score: " + std::to_string(score));
}

// STATE & GAMEPLAY/LOGIC METHODS

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {
    std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
    for (const auto& loc : mappedLocs) {
        if (board.getContent(loc) != Gameboard::EMPTY_BLOCK) {
            return false;
        }
    }
    return isWithinBorders(shape);
}


bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
    std::vector<Point> mappedLocs = shape.getBlockLocsMappedToGrid();
    
    for (const Point& loc : mappedLocs) {
        // Check left, right, and bottom borders
        if (loc.getX() < 0 || loc.getX() >= Gameboard::MAX_X || 
            loc.getY() >= Gameboard::MAX_Y) {
            return false;
        }
    }
    return true;
}

void TetrisGame::determineSecondsPerTick() {
    secondsPerTick = MAX_SECONDS_PER_TICK / (score / 100 + 1);
}