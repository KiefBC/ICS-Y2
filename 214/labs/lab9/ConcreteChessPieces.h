#pragma once
#include "ChessPiece.h"
#include "Blocker.h"

class Knight : public ChessPiece {
public:
    Knight(const Gameboard& gameBoard) : ChessPiece(gameBoard) {}
    
    std::vector<Point> getValidMoves() const {
        return convertOffsetsToValidMoves({
            {1, 2}, {2, 1}, {2, -1}, {1, -2}, 
            {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
        });
    }

    // std::vector<Point> getValidMoves() const override {
    //         std::vector<Point> offsets = {
    //         {1, 2}, {2, 1}, {2, -1}, {1, -2}, 
    //         {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2} 
    //     };

    //     std::vector<Point> validMoves;
    //     Point currentPosition = getPosition();

    //     // for (const Point& offset : offsets) {
    //     //     Point destination = {currentPosition.getX() + offset.getX(), currentPosition.getY() + offset.getY()};
    //     //     if (board.isValidPoint(destination)) {
    //     //         validMoves.push_back(destination);
    //     //     }
    //     // }
    //     for (const Point& offset : offsets) {
    //         Point destination = {currentPosition.getX() + offset.getX(), currentPosition.getY() + offset.getY()};
    //         if (board.isValidPoint(destination)) {
    //             const GameboardItem* item = board.getContent(destination);
    //             if (!dynamic_cast<const Blocker*>(item)) {
    //                 validMoves.push_back(destination);
    //             }
    //         }
    //     }
    //     return validMoves;
    // }
        
    char getDisplayChar() const {
        return 'k';
    }
};

class King : public ChessPiece {
public:
    King(const Gameboard& gameBoard) : ChessPiece(gameBoard) {}
    
    std::vector<Point> getValidMoves() const {
        return convertOffsetsToValidMoves({
            {-1, -1}, {0, -1}, {1, -1},
            {-1, 0},         {1, 0},
            {-1, 1}, {0, 1}, {1, 1}
        });
    }

    char getDisplayChar() const {
        return 'K';
    }
}; 