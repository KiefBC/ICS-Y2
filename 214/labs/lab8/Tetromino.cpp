//
// Created by kiefer on 10/22/24.
//

#include "Tetromino.h"

Tetromino::Tetromino() {
    shape = static_cast<TetShape>(rand() % 7);
    setShape(shape);
}

TetColor Tetromino::getColor() const {
    return color;
}

TetShape Tetromino::getShape() const {
    return shape;
}

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

void Tetromino::rotateClockwise() {
    for (auto& block : blockLocs) {
        int temp = block.getX();
        block.setX(block.getY());
        block.setY(-temp);
    }
}

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