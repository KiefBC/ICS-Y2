#pragma once
#include "ChessPiece.h"
#include "Blocker.h"

class Knight : public ChessPiece {
public:
    Knight(const Gameboard& gameBoard);
    std::vector<Point> getValidMoves() const override;
    char getDisplayChar() const override;
};

class King : public ChessPiece {
public:
    King(const Gameboard& gameBoard);
    std::vector<Point> getValidMoves() const override;
    char getDisplayChar() const override;
}; 