#pragma once
#include "GameboardItem.h"

/// @brief Represents a blocker on the gameboard
class Blocker : public GameboardItem
{
public:
    /// @brief Constructor for Blocker  
    /// @param gameBoard - reference to the gameboard
    Blocker(const Gameboard &gameBoard) : GameboardItem(gameBoard) {}

    /// @brief Returns the display character for the blocker
    /// @return display character
    char getDisplayChar() const override
    {
        return '#';
    }
};
