#pragma once
#include "GameboardItem.h"
#include <vector>

class ChessPiece : public GameboardItem {
public:
    // Constructor
    ChessPiece(const Gameboard& gameBoard) : GameboardItem(gameBoard) {}
    
    // Pure virtual function for getting valid moves
    virtual std::vector<Point> getValidMoves() const = 0;
    
    // Virtual function to check if a move is valid
    virtual bool isValidMove(const Point& destination) {
        std::vector<Point> validMoves = getValidMoves();
        return std::find(validMoves.begin(), validMoves.end(), destination) != validMoves.end();
    }
};
