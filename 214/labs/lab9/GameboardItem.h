#pragma once
#include "Point.h"

class Gameboard;

/// @brief Represents an item on the gameboard
class GameboardItem {
protected:
    Point position;
    const Gameboard& board;
public:
    /// @brief Constructor for GameboardItem
    /// @param gameBoard - reference to the gameboard
    GameboardItem(const Gameboard& gameBoard)
        : position(0, 0), board(gameBoard) {}

    /// @brief Destructor for GameboardItem
    virtual ~GameboardItem() = default;

    /// @brief Get the display character for the GameboardItem
    /// @return The display character
    virtual char getDisplayChar() const = 0;

    /// @brief Get the position of the GameboardItem
    /// @return The position
    Point getPosition() const {
        return position;
    }

    /// @brief Set the position of the GameboardItem
    /// @param newPosition - the new position
    void setPosition(const Point& newPosition) {
        position = newPosition;
    }
};
