#include "Credit.h"

int main() {
  int input;

  std::cout << "Enter a Number: ";
  std::cin >> input;

  int result = getSumOfDigits(input);
  std::cout << "Total Sum of Digits: " << result << std::endl;

  std::string input2;
  std::cout << "Enter a Number: ";
  std::cin >> input2;

  std::string prefix;
  std::cout << "Enter a Prefix: ";
  std::cin >>  prefix;

  bool result2 = startsWith(input2, prefix);

  std::cout << "The Bool Result is: " << (result2 ? "True" : "False") << std::endl;
  
  std::cout << "Testing the Prefix... ";
  if (hasValidPrefix(input2)) {
    std::cout << "True" << std::endl;
  } else {
    std::cout << "False" << std::endl;
  }

  return 0;
} 
