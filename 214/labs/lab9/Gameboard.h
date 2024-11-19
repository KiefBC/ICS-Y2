#pragma once
#include "Point.h"

class GameboardItem;

class Gameboard
{

public:
  // CONSTANTS
  static const int MAX_X = 8; // gameboard x dimension
  static const int MAX_Y = 8; // gameboard y dimension

private:
  // MEMBER VARIABLES -------------------------------------------------
  GameboardItem *grid[MAX_Y][MAX_X]; // a 2D array of pointers to GameboardItem

public:
  // constructor
  // Set all pointers to nullptr
  Gameboard();

  // destructor
  // clear the board - deallocate any objects, set pointers to nullptr
  ~Gameboard();

  // Deallocate (return to heap) any objects (tracked by grid pointers)
  // Set all pointers to nullptr
  void empty();

  // Get the content at a given point
  // assert the point is valid
  // - param 1: a Point object (the XY of the content weant to retrieve)
  // - return: a pointer to the GameboardItem stored at the position specified
  GameboardItem *getContent(const Point &p) const;

  // Set the content at a given point
  // assert the point is valid
  // - param 1: a Point
  // - param 2: the memory address of a GameboardItem that we want to set at
  // this location.
  void setContent(const Point &p, GameboardItem *content);

  // Determine if a given Point's XY is a valid grid location
  // - param 1: a Point object
  // - return: true if the point is on the grid, false otherwise
  bool isValidPoint(const Point &p) const;

  // Print the grid contents to the console (for debugging purposes)
  //   use std::setw(2) to space the contents out (#include <iomanip>).
  // - params: none
  // - return: nothing
  virtual void printToConsole() const;
};
