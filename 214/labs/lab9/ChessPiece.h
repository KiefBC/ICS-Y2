#pragma once
#include "GameboardItem.h"
#include "Gameboard.h"
#include "Blocker.h"
#include <vector>
#include <algorithm>

/// @brief Chess piece
class ChessPiece : public GameboardItem {
public:
    /// @brief Convert offsets to valid moves
    /// @param offsets The offsets
    /// @return The valid moves
    std::vector<Point> convertOffsetsToValidMoves(const std::vector<Point>& offsets) const {
        std::vector<Point> validMoves;
        Point currentPosition = getPosition();

        // Iterate through all offsets  
        for (const Point& offset : offsets) {
            // Calculate the destination point
            // We use the current position and add the offset to get the destination point
            Point destination = {currentPosition.getX() + offset.getX(), currentPosition.getY() + offset.getY()};

            // Check if the destination point is valid
            if (board.isValidPoint(destination)) {
                // Get the content of the destination point
                const GameboardItem* item = board.getContent(destination);
                if (!dynamic_cast<const Blocker*>(item)) {
                    // If the content is not a Blocker, add the destination point to the valid moves
                    validMoves.push_back(destination);
                }
            }
        }
        return validMoves;
    }

    /// @brief Constructor for ChessPiece
    /// @param gameBoard The gameboard
    ChessPiece(const Gameboard& gameBoard) : GameboardItem(gameBoard) {}
    
    /// @brief Pure virtual function for getting valid moves
    /// @return The valid moves
    virtual std::vector<Point> getValidMoves() const = 0;
    
    /// @brief Virtual function to check if a move is valid
    /// @param destination The destination
    /// @return True if the move is valid, false otherwise
    virtual bool isValidMove(const Point& destination) const {
        std::vector<Point> validMoves = getValidMoves();
        return std::find(validMoves.begin(), validMoves.end(), destination) != validMoves.end();
    }
};
