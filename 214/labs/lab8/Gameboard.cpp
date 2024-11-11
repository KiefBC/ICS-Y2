#include "Gameboard.h"

Gameboard::Gameboard() { empty(); }

/// @brief Empties the gameboard by setting all cells to EMPTY_BLOCK.
void Gameboard::empty() {
  for (int y = 0; y < MAX_Y; y++) {
    for (int x = 0; x < MAX_X; x++) {
      grid[y][x] = EMPTY_BLOCK;
    }
  }
}

/// @brief Prints the gameboard to the console by iterating through each cell and printing a block if it is not empty.
void Gameboard::printToConsole() const {
  int half = MAX_Y / 2;
  for (int y = 0; y < half; y++) {
    for (int x = 0; x < MAX_X; x++) {
      if (grid[y][x] == EMPTY_BLOCK) {
        std::cout << std::setw(2) << "\u2661" << " ";
      } else {
        std::cout << std::setw(2) << grid[y][x] << " ";
      }
    }

    std::cout << "   |   ";

    for (int x = 0; x < MAX_X; x++) {
      if (grid[y + half][x] == EMPTY_BLOCK) {
        std::cout << std::setw(2) << "\u2661" << " ";
      } else {
        std::cout << std::setw(2) << grid[y + half][x] << " ";
      }
    }
    std::cout << std::endl;
  }
}

/// @brief Returns the content of the cell at the given coordinates.
/// @param x The x coordinate of the cell.
/// @param y The y coordinate of the cell.
/// @return The content of the cell.
int Gameboard::getContent(int x, int y) const {
    assert(isValidPoint(x, y));
    return grid[y][x];
}

/// @brief Returns the content of the cell at the given point.
/// @param p The point representing the cell.
/// @return The content of the cell.
int Gameboard::getContent(const Point& p) const {
  assert(isValidPoint(p.getX(), p.getY()));
  return grid[p.getY()][p.getX()];
}

/// @brief Sets the content of the cell at the given coordinates to the given value.
/// @param x The x coordinate of the cell.
/// @param y The y coordinate of the cell.
/// @param value The value to set the cell to.
void Gameboard::setContent(int x, int y, int value) {
  if (isValidPoint(x, y)) {
    grid[y][x] = value;
  }
}

/// @brief Sets the content of the cell at the given point to the given value.
/// @param p The point representing the cell.
/// @param value The value to set the cell to.
void Gameboard::setContent(const Point& p, int value) {
  if (isValidPoint(p.getX(), p.getY())) {
    grid[p.getY()][p.getX()] = value;
  }
}

/// @brief Sets the content of the cells at the given points to the given value.
/// @param points The vector of points representing the cells.
/// @param value The value to set the cells to.
void Gameboard::setContent(const std::vector<Point>& points, int value) {
  for (auto& p : points) {
    setContent(p, value);
  }
}

/// @brief Checks if all the given points are empty.
/// @param points The vector of points representing the cells.
/// @return True if all the points are empty, false otherwise.
bool Gameboard::areAllLocsEmpty(std::vector<Point>& points) const {
  for (auto& p : points) {
    if (isValidPoint(p)) {
      if (getContent(p) != EMPTY_BLOCK) {
        return false;
      }
    }
  }
  return true;
}

/// @brief Removes the row at the given index by shifting all rows above it down.
/// @param rowIndex The index of the row to remove.
void Gameboard::removeRow(int rowIndex) {
    assert(rowIndex >= 0 && rowIndex < MAX_Y);
    for (int y = rowIndex; y > 0; y--) {
        copyRowIntoRow(y - 1, y);
    }
    fillRow(0, EMPTY_BLOCK);
}

/// @brief Returns the spawn location of the next shape.
/// @return The spawn location of the next shape.
Point Gameboard::getSpawnLoc() const {
  return spawnLoc;
}

/// @brief Checks if the given row is completed by checking if all cells in the row are not empty.
/// @param rowIndex The index of the row to check.
/// @return True if the row is completed, false otherwise.
bool Gameboard::isRowCompleted(int rowIndex) const {
    assert(rowIndex >= 0 && rowIndex < MAX_Y);
    for (int x = 0; x < MAX_X; x++) {
        if (getContent(x, rowIndex) == EMPTY_BLOCK) {
            return false;
        }
    }
    return true;
}

/// @brief Fills the given row with the given value by iterating through each cell in the row and setting its content.
/// @param rowIndex The index of the row to fill.
/// @param value The value to set the cells to.
void Gameboard::fillRow(int rowIndex, int value) {
  for (int x = 0; x < MAX_X; x++) {
    setContent(Point(x, rowIndex), value);
  }
}

/// @brief Returns a vector of the indices of the completed rows.
/// @return A vector of the indices of the completed rows.
std::vector<int> Gameboard::getCompletedRowIndices() const {
  std::vector<int> completedRows;
  for (int y = 0; y < MAX_Y; y++) {
    if (isRowCompleted(y)) {
      completedRows.push_back(y);
    }
  }
  return completedRows;
}

/// @brief Removes the rows at the given indices by calling removeRow for each index.
/// @param rowIndices The vector of indices of the rows to remove.
void Gameboard::removeRows(std::vector<int>& rowIndices) {
  for (int& y : rowIndices) {
    removeRow(y);
  }
}

/// @brief Removes the completed rows and returns the number of rows removed.
/// @return The number of rows removed.
int Gameboard::removeCompletedRows() {
  std::vector<int> completedRows = getCompletedRowIndices();
  removeRows(completedRows);
  return completedRows.size();
}

/// @brief Copies the content of the source row into the target row by iterating through each cell in the source row and setting the content of the corresponding cell in the target row.
/// @param sourceRowIndex The index of the source row.
/// @param targetRowIndex The index of the target row.
void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {
    assert(sourceRowIndex >= 0 && sourceRowIndex < MAX_Y);
    assert(targetRowIndex >= 0 && targetRowIndex < MAX_Y);
    for (int x = 0; x < MAX_X; x++) {
        setContent(x, targetRowIndex, getContent(x, sourceRowIndex));
    }
}

/// @brief Checks if the given point is valid by checking if the x and y coordinates are within the bounds of the gameboard.
/// @param p The point to check.
/// @return True if the point is valid, false otherwise.
bool Gameboard::isValidPoint(const Point& p) const {
  return p.getX() >= 0 && p.getX() < MAX_X &&
         p.getY() >= 0 && p.getY() < MAX_Y;
}

/// @brief Checks if the given coordinates are valid by checking if the x and y coordinates are within the bounds of the gameboard.
/// @param x The x coordinate to check.
/// @param y The y coordinate to check.
/// @return True if the coordinates are valid, false otherwise.
bool Gameboard::isValidPoint(int x, int y) const {
  return x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y;
}
