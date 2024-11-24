#include "TestSuite.h"
// #include "DebugNewOp.h"
#include "MyVector.h"

#include <exception>
#include <iostream>

int main() {

  // new int{1};
  // _CrtMemDumpAllObjectsSince(nullptr);
 // try {
 //   MyVector v(3);
 //   v.set(0, 1);
 //   v.get(0);
 //   int vectorSize = v.size();
 //   std::cout << "Vector size: " << vectorSize << "\n";
 // } catch (std::exception &e) {
 //   std::cout << "Exception: " << e.what() << "\n";
 // } catch (...) {
 //   std::cout << "Unknown exception\n";
 // }
  
  TestSuite::runTestSuite();

  return 0;
}
