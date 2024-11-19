#pragma once
#include "ChessPiece.h"
#include "Blocker.h"

/// @brief Knight piece
class Knight : public ChessPiece {
public:
    /// @brief Constructor for Knight   
    /// @param gameBoard The gameboard
    Knight(const Gameboard& gameBoard);
    
    /// @brief Get the valid moves for the Knight
    /// @return The valid moves
    std::vector<Point> getValidMoves() const override;

    /// @brief Get the display character for the Knight
    /// @return The display character
    char getDisplayChar() const override;
};

/// @brief King piece
class King : public ChessPiece {
public: 
    /// @brief Constructor for King
    /// @param gameBoard The gameboard
    King(const Gameboard& gameBoard);

    /// @brief Get the valid moves for the King
    /// @return The valid moves
    std::vector<Point> getValidMoves() const override;

    /// @brief Get the display character for the King
    /// @return The display character
    char getDisplayChar() const override;
}; 