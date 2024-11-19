#include "ConcreteChessPieces.h"

Knight::Knight(const Gameboard& gameBoard) : ChessPiece(gameBoard) {}

std::vector<Point> Knight::getValidMoves() const {
    return convertOffsetsToValidMoves({
        {1, 2}, {2, 1}, {2, -1}, {1, -2}, 
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    });
}

char Knight::getDisplayChar() const {
    return 'k';
}

King::King(const Gameboard& gameBoard) : ChessPiece(gameBoard) {}

std::vector<Point> King::getValidMoves() const {
    return convertOffsetsToValidMoves({
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},         {1, 0},
        {-1, 1}, {0, 1}, {1, 1}
    });
}

char King::getDisplayChar() const {
    return 'K';
} 