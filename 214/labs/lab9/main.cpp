#include "Gameboard.h"
#include "TestSuite.h"

int main() {
    Gameboard board;
    
    // Test the Gameboard constructor
    Gameboard* gameboard = new Gameboard();
    
    // Print the board
    gameboard->printToConsole();
    
    return 0;
} 
