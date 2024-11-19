#include "Gameboard.h"
#include "TestSuite.h"
#include "ConcreteChessPieces.h"
#include "Blocker.h"
int main() {
    Gameboard board;
    TestSuite::runTestSuite();

    board.setContent(Point(3, 1), new Blocker(board));
    board.setContent(Point(4, 0), new King(board));
    board.setContent(Point(1, 0), new Knight(board));
    board.printToConsole();
    
    return 0;
} 
