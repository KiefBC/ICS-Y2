#pragma once
#include "Gameboard.h"
#include "ChessPiece.h"
#include "Point.h"


// Specifying locations on a board is done with a col
struct ColRowPair {
    char col{ };    // ['a'..'h']
    char row{ };    // ['1'..'8']
};

class Chessboard : public Gameboard {
public:
    static const int COLOR_ACTIVE_PIECE{ 10 };     // green
    static const int COLOR_VALID_MOVE{ 12 };       // red
    static const int COLOR_NORMAL{ 15 };           // white
    static const int COLOR_ROW_COL_GUIDE{ 6 };     // orange            

    // Determine if both the col ['a'..'h'] and row ['1'..'8'] are in range
    // - param1: a ColRowPair
    // - return: true if in range, false otherwise
    bool isColRowValid(const ColRowPair& crPair);


    // Given a ColRowPair (2 chars representing a board row/col), convert it to a 
    // Point that can be used by the Chessboard's 2D array to represent the same location.
    //  eg: {'a','8'} -> Point(0,0)
    //  eg: {'h','1'} -> Point(7,7)
    // - param1: a ColRowPair
    // - return: the equivalent Point (XY position)
    Point convertColRowToPoint(const ColRowPair& crPair);


    // Set the content at a specific row/col pair.
    // To accomplish this: 
    // - param1: ColRowPair position.
    // - param2: the GameboardItem we want to set.
    using Gameboard::setContent; // this allows either the base or derived version to be called
    void setContent(const ColRowPair& crPair, GameboardItem* pPiece);


    // Determine the text color for the Gameboard point being examined.
    // Color will depend on what targetPoint contains and if there is an active chess piece:
    //    - the active chess piece
    //    - a valid move
    //    - nothing special (a normal spot)
    /// - param1: the point being examined
    /// - param2: a vector of valid moves for the "active piece" 
    /// - return: the color that we should use to color this point.
    int getTextColorForPoint(const Point& targetPoint, ChessPiece* pActiveChessPiece = nullptr) const;


    // Print the grid contents to the console (for debugging purposes)
    // - params: none
    // - return: nothing
    void printToConsole(ChessPiece* pActivePiece = nullptr) const;

};
