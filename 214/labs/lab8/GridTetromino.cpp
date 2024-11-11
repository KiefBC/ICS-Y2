#include "GridTetromino.h"
#include "TestSuite.h"
#include <iostream>
#include "Point.h"

/// @brief Default constructor for GridTetromino.
/// @details Initializes the grid location to (0, 0).
GridTetromino::GridTetromino() {
    gridLoc = Point(0, 0);
}

/// @brief Returns the grid location of the tetromino.
/// @return The grid location of the tetromino.
Point GridTetromino::getGridLoc() const {
    return gridLoc;
}

/// @brief Sets the grid location of the tetromino to the given coordinates.
/// @param x The x-coordinate to set the grid location to.
/// @param y The y-coordinate to set the grid location to.
void GridTetromino::setGridLoc(int x, int y) {
    gridLoc = Point(x, y);
}

/// @brief Sets the grid location of the tetromino to the given point.
/// @param p The Point to set the grid location to.
void GridTetromino::setGridLoc(const Point& p) {
    gridLoc = p;
}

/// @brief Moves the grid location of the tetromino by the given offsets.
/// @param xOffset The x-coordinate offset to move the grid location.
/// @param yOffset The y-coordinate offset to move the grid location.
void GridTetromino::move(int xOffset, int yOffset) {
    Point newLoc = Point(gridLoc.getX() + xOffset, gridLoc.getY() + yOffset);
    gridLoc = newLoc;
}

/// @brief Returns a vector of Points representing the block locations mapped to the grid.
/// @return A vector of Points representing the block locations mapped to the grid.
std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {
    std::vector<Point> mappedBlocks;
    for (const Point& p : blockLocs) {
        mappedBlocks.push_back(Point(gridLoc.getX() + p.getX(), gridLoc.getY() + p.getY()));
    }
    return mappedBlocks;
}

/// @brief Main function to run the test suite.
/// @return 0 if the test suite runs successfully.
int main() {
    TestSuite::runTestSuite();
    return 0;
}