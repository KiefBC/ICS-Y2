#include "Chessboard.h"
#include "ConcreteChessPieces.h"
#include "Blocker.h"
#include "ChessGame.h"
#include <iostream>
#include <string>
#include <fstream>

ChessGame::ChessGame()
{    
    board.setContent(ColRowPair{ 'd', '7' }, new Blocker(board));
    board.setContent(ColRowPair{ 'e', '8' }, new King(board));
    board.setContent(ColRowPair{ 'b', '8' }, new Knight(board));
}


ChessGame::~ChessGame() {
    pActiveChessPiece = nullptr;
}

void ChessGame::showMenu() {
    std::cout << "  [a??] set active piece (eg: ac5)\n";
    std::cout << "  [m??] move active piece (eg: mc5)\n";
    std::cout << "  [s] save board to file\n"; 
    std::cout << "  [q] quit\n";
}


Command ChessGame::convertInputToCommand(const std::string& input) {
    Command command;
    if (input.length() >= 1) {
        switch (input[0]) {
        case 'a':
            if (input.length() >= 3) {
                command.action = Action::setActivePiece;
                command.loc.col = input[1];
                command.loc.row = input[2];
                command.isValid = board.isColRowValid(command.loc);
            }
            break;
        case'm':
            if (input.length() >= 3) {
                command.action = Action::moveActivePiece;
                command.loc.col = input[1];
                command.loc.row = input[2];
                command.isValid = board.isColRowValid(command.loc);
            }
            break;
        case 's':           
            command.action = Action::save;
            command.isValid = true;           
            break;

        case 'q':
            command.action = Action::quit;
            command.isValid = true;
            break;
        }        
    } 
    return command;
}


Command ChessGame::promptForCommand() {
    std::string input{};
    std::cout << "Command?: ";
    std::getline(std::cin, input);
    return convertInputToCommand(input);
}


void ChessGame::handleCommand(const Command& command) {

    if (command.isValid) {
        switch (command.action) {

        case Action::setActivePiece:
            std::cout << "Setting active piece to: [col:" << command.loc.col << ", row:" << command.loc.row << "].\n";
            setActiveChessPiece(command.loc);
            break;

        case Action::moveActivePiece:            
            std::cout << "Moving active piece to: [col:" << command.loc.col << ", row:" << command.loc.row << "].\n";
            moveActiveChessPiece(command.loc);            
            break;

        case Action::save:
            std::cout << "Saving to file.\n";
            saveToFile(Constants::saveFilename);
            break;

        }
    }
    else {
        std::cout << "Invalid command.\n";
    }  
    std::cout << "\n";
}


void ChessGame::runGameLoop() {
    bool active = true;
    Command cmd;
    do { 
        board.printToConsole(pActiveChessPiece);
        showMenu();
        cmd = promptForCommand();
        handleCommand(cmd);       
    } while (cmd.action != Action::quit);

    std::cout << "Exiting game.\n";
}



bool ChessGame::setActiveChessPiece(const ColRowPair& crPair) {
    if (!board.isColRowValid(crPair)) {
        std::cout << "Invalid col/row pair.\n";
        return false;
    } // Row and column are valid

    Point point = board.convertColRowToPoint(crPair);
    if (!board.isValidPoint(point)) {
        std::cout << "Invalid point.\n";
        return false;
    } // Point is valid

    GameboardItem* item = board.getContent(point);
    if (!item) {
        std::cout << "No item at point.\n";
        return false;
    } // Item is valid

    ChessPiece* chessPiece = dynamic_cast<ChessPiece*>(item);
    if (!chessPiece) {
        std::cout << "Item is not a chess piece.\n";
        return false;
    } // Item is a chess piece

    pActiveChessPiece = chessPiece;
    std::cout << "Successfully set active piece to " << chessPiece->getDisplayChar() << " at position " 
              << crPair.col << crPair.row << ".\n";

    return true;
}

bool ChessGame::moveActiveChessPiece(const ColRowPair& crPair) {
    // TODO: Steps:    
    //   -ensure there's an active chess piece (if not: error msg & return false)
    //   -convert col/row pair to point (if point invalid: error message & return false)
    //   -check if the point is a valid move for the active chess piece (if not: error message & return false)
    //   -check if there is a chess piece at the point, if so, capture it (delete it & output message)
    //   -remove the active piece from its current position on the board (set the board content to nullptr)
    //   -set the board content at the point to be the active chess piece & return true

    if (!pActiveChessPiece) {
        std::cout << "No active chess piece.\n";
        return false;
    } // There is an active chess piece

    Point point = board.convertColRowToPoint(crPair);
    if (!board.isValidPoint(point)) {
        std::cout << "Invalid point.\n";
        return false;
    } // Point is valid

    std::vector<Point> validMoves = pActiveChessPiece->getValidMoves();
    if (std::find(validMoves.begin(), validMoves.end(), point) == validMoves.end()) {
        std::cout << "Invalid move.\n";
        return false;
    } // Move is valid
    
    GameboardItem* item = board.getContent(point);
    if (item) {
        std::cout << "Capturing " << item->getDisplayChar() << " at " << crPair.col << crPair.row << ".\n";
        delete item;
    }

    board.setContent(point, pActiveChessPiece);
    std::cout << "Successfully moved active piece to " << crPair.col << crPair.row << ".\n";
    return true;
}


void ChessGame::saveToFile(const char* filename)
{
    std::ofstream saveFile(filename);
    if (saveFile) {
        // TODO: once Chessboard implements ISerializable, comment this next line back in.
        //saveFile << board.toString();   
        saveFile.close();
    }
    else {
        std::cout << "Error writing to savefile.\n";
    }   
}

