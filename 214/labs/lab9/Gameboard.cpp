#include "Gameboard.h"
#include <cassert>
#include <iomanip>
#include <iostream>

Gameboard::Gameboard()
    : grid() // this is a way to init an array of pointers to all be nullptr
{}

Gameboard::~Gameboard() { empty(); }

void Gameboard::empty() {
  for (int y = 0; y < MAX_Y; y++) {
    for (int x = 0; x < MAX_X; x++) {
      // deallocate (return to heap) the contents of pointers that are not
      // nullptr
      if (grid[y][x]) {
        delete grid[y][x];
      }
      grid[y][x] = nullptr; // clear all the pointers
    }
  }
}

void Gameboard::printToConsole() const {
  for (int y = 0; y < MAX_Y; y++) {
    for (int x = 0; x < MAX_X; x++) {
      std::cout << std::setw(2);
      GameboardItem *pItem = getContent(Point(x, y));
      if (pItem) {
        std::cout << pItem->getDisplayChar();
      } else {
        std::cout << ".";
      }
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

bool Gameboard::isValidPoint(const Point &p) const {
  return p.getX() >= 0 && p.getX() < MAX_X && p.getY() >= 0 && p.getY() < MAX_Y;
}

GameboardItem *Gameboard::getContent(const Point &p) const {
  assert(isValidPoint(p) && "Error: Gameboard.getContent() - invalid point.");
  return grid[p.getY()][p.getX()];
}

void Gameboard::setContent(const Point &p, GameboardItem *pItem) {
  assert(isValidPoint(p) &&
         "Error: Gameboard.setContent() - point is not valid");

  // tell the grid that it now contains a new GameboardItem
  grid[p.getY()][p.getX()] = pItem;

  // update the GameboardItem's position (if we're using one)
  if (pItem) {
    pItem->setPosition(p);
  }
}
