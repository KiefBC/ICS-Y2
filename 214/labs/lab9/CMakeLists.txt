cmake_minimum_required(VERSION 3.10)
project(ChessGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    Blocker.h
    Chessboard.cpp
    Chessboard.h
    ChessGame.cpp
    ChessGame.h
    ChessPiece.h
    ConcreteChessPieces.cpp
    ConcreteChessPieces.h
    Gameboard.cpp
    Gameboard.h
    GameboardItem.h
    ISerializable.h
    Point.h
    TestSuite.cpp
)

# Create test executable
add_executable(TestSuite ${SOURCES})

# Enable testing
enable_testing()
add_test(NAME TestSuite COMMAND TestSuite)