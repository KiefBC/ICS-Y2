#include "Gameboard.h"
#include "TestSuite.h"
#include "ConcreteChessPieces.h"
#include "Blocker.h"
#include "Chessboard.h"
#include "ChessGame.h"


int main() {
    // Gameboard board;
    // board.setContent(Point(3, 1), new Blocker(board));
    // board.setContent(Point(4, 0), new King(board));
    // board.setContent(Point(1, 0), new Knight(board));

    // Chessboard board;
    // board.setContent(ColRowPair{ 'd', '7' }, new Blocker(board));
    // board.setContent(ColRowPair{ 'e', '8' }, new King(board));
    // board.setContent(ColRowPair{ 'b', '8' }, new Knight(board));
    // board.printToConsole();

    ChessGame game;
    game.runGameLoop();

    // TestSuite::runTestSuite();
    
    return 0;
} 
