#include <iostream>
#include <iomanip>
#include <cassert>
//#include <windows.h> // Disable this for Linux
#include <iomanip>
#include "Chessboard.h"
#include <vector>


bool Chessboard::isColRowValid(const ColRowPair& crPair) {
    return  crPair.row >= '1' && crPair.row <= '8' &&
            crPair.col >= 'a' && crPair.col <= 'h';
}

Point Chessboard::convertColRowToPoint(const ColRowPair& crPair) {
    // translate col/row to Point
    int colIndex = crPair.col - 'a';
    int rowIndex = '8' - crPair.row;
    Point pt(colIndex, rowIndex);

    // assert that the Point is valid
    assert(isValidPoint(pt) && "invalid chessboard point");

    return pt;
}


void Chessboard::setContent(const ColRowPair& crPair, GameboardItem* pItem) {
    // convert col/row to point
    Point targetPos = convertColRowToPoint(crPair);

    // call the derived version of setContent() to set the content
    Gameboard::setContent(targetPos, pItem);  
}


int Chessboard::getTextColorForPoint(const Point& targetPoint, ChessPiece* pActiveChessPiece ) const {
    // if the targetPoint is the active chess piece, return the active piece color
    if (pActiveChessPiece && (targetPoint == pActiveChessPiece->getPosition())) {
        return COLOR_ACTIVE_PIECE;
    }

    // determine if the targetPoint is a valid move
    bool isValidMove = false;
 
    // determine valid moves for the active piece
    std::vector<Point> validMovesForActivePiece;
    if (pActiveChessPiece) {
        validMovesForActivePiece = pActiveChessPiece->getValidMoves();
    }

    // is the point we're examining a valid move?
    for (const Point& validMove : validMovesForActivePiece) {
        if (validMove == targetPoint) {
            isValidMove = true;
        }
    }

    // if the targetPoint is a valid move, use the valid move color
    if (isValidMove) {
        return COLOR_VALID_MOVE;
    }

    // if we get this far, there's nothing special about the targetPoint
    return COLOR_NORMAL;
}


// void Chessboard::printToConsole(ChessPiece* pActiveChessPiece) const {
//     // go through each row
//     for (int y = 0; y < MAX_Y; y++) {

//         // output the left hand guide for rows ['8'..'1'])
//         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Chessboard::COLOR_ROW_COL_GUIDE);
//         std::cout << (8 - y) << " | ";

//         // go through each column
//         for (int x = 0; x < MAX_X; x++) {
//             std::cout << std::setw(2);  // set the width to 2 characters

//             // get the color for the point we're about to print
//             Point currentPoint(x, y);
//             int color = getTextColorForPoint(currentPoint, pActiveChessPiece);
//             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

//             // determine which character to print 
//             GameboardItem* pItem = getContent(currentPoint);
//             if (pItem) {
//                 std::cout << pItem->getDisplayChar();
//             }
//             else {
//                 std::cout << ".";
//             }
//         }
//         std::cout << "\n";
//     }
//     // output the lower guide for columns ['a'..'h']
//     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Chessboard::COLOR_ROW_COL_GUIDE);
//     std::cout << "    ----------------\n";
//     std::cout << "     a b c d e f g h \n";
//     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Chessboard::COLOR_NORMAL);   // restore color 
//     std::cout << "\n";
// }

// This works for Linux
void Chessboard::printToConsole(ChessPiece* pActiveChessPiece) const {
    // go through each row
    for (int y = 0; y < MAX_Y; y++) {
        // output the left hand guide for rows ['8'..'1'])
        std::cout << " \033[37m" << (8 - y) << " | "; // white color for guide

        // go through each column
        for (int x = 0; x < MAX_X; x++) {
            std::cout << std::setw(2);
            // get the color for the point we're about to print
            Point currentPoint(x, y);
            int color = getTextColorForPoint(currentPoint, pActiveChessPiece);
            
            // Convert color code to ANSI
            switch(color) {
                case COLOR_ACTIVE_PIECE: std::cout << "\033[32m"; break; // green
                case COLOR_VALID_MOVE: std::cout << "\033[34m"; break;   // blue
                default: std::cout << "\033[37m"; break;                 // white
            }

            // determine which character to print 
            GameboardItem* pItem = getContent(currentPoint);
            if (pItem) {
                std::cout << pItem->getDisplayChar() << " ";  // Add space after character
            }
            else {
                std::cout << ". ";  // Add space after dot
            }
        }
        std::cout << "\n";
    }
    // output the lower guide for columns ['a'..'h']
    std::cout << "\033[37m";  // white color for guide
    std::cout << "    ----------------\n";
    std::cout << "     a b c d e f g h \n";
    std::cout << "\033[0m\n";  // reset color
}

std::string Chessboard::toString() const {
    std::string result;
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            GameboardItem* pItem = getContent(Point(x, y));
            if (pItem) {
                result += pItem->getDisplayChar();
            } else {
                result += '.';
            }
        }
        result += '\n';
    }
    return result;
}



