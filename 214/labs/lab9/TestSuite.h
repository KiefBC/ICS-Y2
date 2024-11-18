#ifndef TESTSUITE_H
#define TESTSUITE_H

// This class runs some automated testing for Lab 9 classes
// Two steps are required to activate it:
// 1) Call TestSuite::runTestSuite() from main()
// 2) Uncomment the #define statements directly below (as you're ready to test each class):
//-----------------------------------------------------------------------
#define POINT
//#define CONCRETE_CHESS_PIECES
//#define CHESSGAME


class TestSuite {

private:	
	static bool testPointClass();			// tests for the Point class
	static bool testConcreteChessPieces();	// tests for the King & Knight classes
	static bool testChessGame();
	


public:
	// This will run a series of tests on the Point and Tetromino classes
	// when the #define statements at the top of this file are active.
	static bool runTestSuite();
};


#endif // !TESTSUITE_H
