#pragma once
#include "Point.h"

class Gameboard;

class GameboardItem {
protected:
    Point position;
    const Gameboard& board;
private:
public:
  // constructor
  GameboardItem(const Gameboard& gameBoard)
      : position(0, 0), board(gameBoard) {}

  // destructor
  virtual ~GameboardItem() = default;

  virtual char getDisplayChar() const = 0;

  Point getPosition() const {
    return position;
  }
  void setPosition(const Point& newPosition) {
    position = newPosition;
  }
};
