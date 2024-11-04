#include "./Gameboard.h"
#include <iomanip>
#include <cassert>

Gameboard::Gameboard() { empty(); }

void Gameboard::empty() {
  for (int y = 0; y < MAX_Y; y++) {
    for (int x = 0; x < MAX_X; x++) {
      grid[y][x] = EMPTY_BLOCK;
    }
  }
}

// void Gameboard::printToConsole() const {
//   for (int y = 0; y < MAX_Y; y++) {
//     for (int x = 0; x < MAX_X; x++) {
//       if (grid[y][x] == EMPTY_BLOCK) {
//         std::cout << std::setw(2) << "\u2661" << " ";
//       } else {
//         std::cout << std::setw(2) << grid[y][x] << " ";
//       }
//     }
//     std::cout << std::endl;
//   }
// }

// void Gameboard::printToConsole() const {
//   int half = MAX_Y / 2; // Split point for the two boards
//   for (int y = 0; y < MAX_Y; y++) {
//     for (int x = 0; x < MAX_X; x++) {
//       if (grid[y][x] == EMPTY_BLOCK) {
//         std::cout << std::setw(2) << "\u2661" << " ";
//       } else {
//         std::cout << std::setw(2) << grid[y][x] << " ";
//       }
//     }
//     std::cout << std::endl;
//     // Insert a separator after the first board
//     if (y == half - 1) {
//       std::cout << std::string(MAX_X * 3, '-') << std::endl; // Adjust length as needed
//     }
//   }
// }

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

// THIS DOES NOT WORK
// int Gameboard::getContent(Point p) const {
//     assert(isValidPoint(p.getX(), p.getY()));
//     return grid[p.getY()][p.getX()];
// }

int Gameboard::getContent(int x, int y) const {
    assert(isValidPoint(x, y));
    return grid[y][x];
}

int Gameboard::getContent(const Point& p) const {
  assert(isValidPoint(p.getX(), p.getY()));
  // if (isValidPoint(p.getX(), p.getY())) {
  //   return grid[p.getY()][p.getX()];
  // }
  // return EMPTY_BLOCK;
  return grid[p.getY()][p.getX()];
}

// THIS WORKS BOTH WAYS
// int Gameboard::getContent(int x, int y) const {
//     if (isValidPoint(x, y)) {
//         return grid[y][x];
//     }
//     return EMPTY_BLOCK;
// }

void Gameboard::setContent(int x, int y, int value) {
  if (isValidPoint(x, y)) {
    grid[y][x] = value;
  }
}

void Gameboard::setContent(Point p, int value) {
  if (isValidPoint(p.getX(), p.getY())) {
    grid[p.getY()][p.getX()] = value;
  }
}

void Gameboard::setContent(std::vector<Point> points, int value) {
  for (Point p : points) {
    setContent(p, value);
  }
}

bool Gameboard::areAllLocsEmpty(std::vector<Point> points) const {
  for (Point p : points) {
    if (getContent(p) != EMPTY_BLOCK) {
      return false;
    }
  }
  return true;
}

void Gameboard::removeRow(int rowIndex) {
    assert(rowIndex >= 0 && rowIndex < MAX_Y);
    for (int y = rowIndex; y > 0; y--) {
        copyRowIntoRow(y - 1, y);
    }
    fillRow(0, EMPTY_BLOCK);
}

// THIS WORKS BOTH WAYS
// void Gameboard::removeRow(int rowIndex) {
//   for (int y = rowIndex; y > 0; y--) {
//     copyRowIntoRow(y - 1, y);
//   }

//   fillRow(0, EMPTY_BLOCK);
// }


Point Gameboard::getSpawnLoc() const {
  return spawnLoc;
}

bool Gameboard::isRowCompleted(int rowIndex) const {
    assert(rowIndex >= 0 && rowIndex < MAX_Y);
    for (int x = 0; x < MAX_X; x++) {
        if (getContent(x, rowIndex) == EMPTY_BLOCK) {
            return false;
        }
    }
    return true;
}

// THIS WORKS BOTH WAYS
// bool Gameboard::isRowCompleted(int rowIndex) const {
//   for (int x = 0; x < MAX_X; x++) {
//     if (getContent(x, rowIndex) == EMPTY_BLOCK) {
//       return false;
//     }
//   }
//   return true;
// }

void Gameboard::fillRow(int rowIndex, int value) {
  for (int x = 0; x < MAX_X; x++) {
    setContent(Point(x, rowIndex), value);
  }
}

std::vector<int> Gameboard::getCompletedRowIndices() const {
  std::vector<int> completedRows;
  for (int y = 0; y < MAX_Y; y++) {
    if (isRowCompleted(y)) {
      completedRows.push_back(y);
    }
  }
  return completedRows;
}

void Gameboard::removeRows(std::vector<int> rowIndices) {
  for (int y : rowIndices) {
    removeRow(y);
  }
}

int Gameboard::removeCompletedRows() {
  std::vector<int> completedRows = getCompletedRowIndices();
  removeRows(completedRows);
  return completedRows.size();
}

void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {
    assert(sourceRowIndex >= 0 && sourceRowIndex < MAX_Y);
    assert(targetRowIndex >= 0 && targetRowIndex < MAX_Y);
    for (int x = 0; x < MAX_X; x++) {
        setContent(x, targetRowIndex, getContent(x, sourceRowIndex));
    }
}

// THIS WORKS BOTH WAYS
// void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {
//   for (int x = 0; x < MAX_X; x++) {
//     setContent(x, targetRowIndex, getContent(x, sourceRowIndex));
//   }
// }

bool Gameboard::isValidPoint(Point p) const {
  return p.getX() >= 0 && p.getX() < MAX_X &&
         p.getY() >= 0 && p.getY() < MAX_Y;
}

bool Gameboard::isValidPoint(int x, int y) const {
  return x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y;
}
