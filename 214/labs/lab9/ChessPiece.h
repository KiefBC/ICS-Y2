#pragma once
#include "GameboardItem.h"
#include "Blocker.h"
#include <vector>
#include <algorithm>

class ChessPiece : public GameboardItem {
protected:
    std::vector<Point> convertOffsetsToValidMoves(const std::vector<Point>& offsets) const {
        std::vector<Point> validMoves;
        Point currentPosition = getPosition();

        for (const Point& offset : offsets) {
            Point destination = {currentPosition.getX() + offset.getX(), currentPosition.getY() + offset.getY()};
            if (board.isValidPoint(destination)) {
                const GameboardItem* item = board.getContent(destination);
                if (!dynamic_cast<const Blocker*>(item)) {
                    validMoves.push_back(destination);
                }
            }
        }
        return validMoves;
    }

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
