#pragma once
#include "Chessboard.h"

namespace Constants {
    const char saveFilename[] = "save.txt";
}

enum class Action { setActivePiece, moveActivePiece, save, quit, unknown };


struct Command {
    Action action{ Action::unknown };
    ColRowPair loc;
    bool isValid{ false };
};


class ChessGame  {
    friend class TestSuite;
private:
    Chessboard board;                           // the chess board       
    ChessPiece* pActiveChessPiece{ nullptr };   // the active chess piece (if any)

public:
    // constructor
    ChessGame();

    // destructor
    ~ChessGame();

     // The loop responsible for displaying the board, and processing commands until it is time to exit
    void runGameLoop();

    // Display the menu options
    void showMenu();
    
    // Prompt the user for a command, return the result in a Command instance.
    Command promptForCommand();

    // Convert string input in to a Command
    Command convertInputToCommand(const std::string& input);
 
    // Given a command, call the appropriate fuctionality in the program.
    void handleCommand(const Command& command );

    // If the row/column passed in has a chess piece on it, then set the Chessboard's 
    // "active piece" pointer to point to it. 
    // - param1: a ColRowPair for the location we expect to find a ChessPiece at
    // - return: true if the "active piece" pointer was successfully set to a chess piece, false otherwise.
    bool setActiveChessPiece(const ColRowPair& crPair);

    /// Move the active piece to a new location
    /// - param1: the ColRowPair for where the active piece should move.
    /// - return: true if the piece was successfully set, false otherwise.
    bool moveActiveChessPiece(const ColRowPair& crPair);

    // Save this chess game to a file.
    void saveToFile(const char* filename);  
};


