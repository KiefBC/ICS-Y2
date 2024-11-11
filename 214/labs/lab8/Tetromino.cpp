#include "Tetromino.h"

/// @brief Constructor that sets a random shape.
Tetromino::Tetromino() {
    shape = static_cast<TetShape>(rand() % 7);
    setShape(shape);
}

/// @brief Returns the color of the tetromino.
/// @return The color of the tetromino.
TetColor Tetromino::getColor() const {
    return color;
}

/// @brief Returns the shape of the tetromino.
/// @return The shape of the tetromino.
TetShape Tetromino::getShape() const {
    return shape;
}

/// @brief Sets the shape of the tetromino to the given shape.
/// @param newShape The shape to set the tetromino to.
void Tetromino::setShape(TetShape newShape) {
    this->shape = newShape;
    blockLocs.clear();

    switch (newShape) {
        case TetShape::I:
            color = TetColor::BLUE_LIGHT;
            blockLocs = {Point(0, 0), Point(0, 1), Point(0, 2), Point(0, 3)};
            break;
        case TetShape::J:
            color = TetColor::BLUE_DARK;
            blockLocs = {Point(0, 0), Point(0, 1), Point(0, 2), Point(1, 0)};
            break;
        case TetShape::L:
            color = TetColor::ORANGE;
            blockLocs = {Point(0, 0), Point(0, 1), Point(0, 2), Point(1, 2)};
            break;
        case TetShape::O:
            color = TetColor::YELLOW;
            blockLocs = {Point(0, 0), Point(1, 0), Point(0, 1), Point(1, 1)};
            break;
        case TetShape::S:
            color = TetColor::GREEN;
            blockLocs = {Point(0,0), Point(1,0), Point(1, 1), Point(2,1)};
            break;
        case TetShape::T:
            color = TetColor::PURPLE;
            blockLocs = {Point(0, 0), Point(1, 0), Point(2, 0), Point(1, 1)};
            break;
        case TetShape::Z:
            color = TetColor::RED;
            blockLocs = {Point(0, 1), Point(1, 1), Point(1, 0), Point(2, 0)};
            break;
    }
}

/// @brief Rotates the tetromino 90 degrees clockwise.
/// @details If the shape is O, it does nothing. Otherwise, it transposes the block locations of the tetromino.
void Tetromino::rotateClockwise() {
    if (shape == TetShape::O) return;

    for (auto& block : blockLocs) {
        int temp = block.getX();
        block.setX(block.getY());
        block.setY(-temp);
    }
}

/// @brief Prints the tetromino to the console.
/// @details Prints the tetromino to the console by iterating through each cell in a 5x5 grid and checking if the cell contains a block.
void Tetromino::printToConsole() const {
    for (int y = 2; y >= -2; --y) {
        for (int x = -2; x <= 2; ++x) {
            bool isBlock = false;
            for (const auto& block : blockLocs) {
                if (block.getX() == x && block.getY() == y) {
                    std::cout << 'X';
                    isBlock = true;
                    break;
                }
            }
            if (!isBlock) std::cout << '.';
        }
        std::cout << std::endl;
    }
}