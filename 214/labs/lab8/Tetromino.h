#ifndef LAB6_TETROMINO_H
#define LAB6_TETROMINO_H

#include <vector>
#include "Point.h"

// Enum for the color of the Tetromino
enum class TetColor {
    RED,
    GREEN,
    BLUE_LIGHT,
    YELLOW,
    BLUE_DARK,
    PURPLE,
    ORANGE
};

// Enum for the shape of the Tetromino
enum class TetShape {
    I,
    J,
    L,
    O,
    S,
    T,
    Z
};

class Tetromino {
    friend class TestSuite; // Giving access to test cases
    friend class GridTetromino;
public:
    // Default constructor
    Tetromino();

    // Getters
    TetColor getColor() const;
    TetShape getShape() const;

    // Setters
    void setShape(TetShape shape);

    // Rotate the Tetromino 90 degrees clockwise
    void rotateClockwise();

    // Print the Tetromino to the console
    void printToConsole() const;
private:
    TetColor color;
    TetShape shape;

    std::vector<Point> blockLocs;
};

#endif //TETROMINO_H
