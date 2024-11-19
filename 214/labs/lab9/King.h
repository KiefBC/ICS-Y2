#pragma once
#include "ChessPiece.h"

class King : public ChessPiece {
public:
    King(const Gameboard& gameBoard) : ChessPiece(gameBoard) {}
    
    std::vector<Point> getValidMoves() const override;
    char getDisplayChar() const override;
}; 