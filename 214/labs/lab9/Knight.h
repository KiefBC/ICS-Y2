#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece {
public:
    Knight(const Gameboard& gameBoard) : ChessPiece(gameBoard) {}
    
    std::vector<Point> getValidMoves() const override;
    char getDisplayChar() const override;
}; 