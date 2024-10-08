#include "test.h"

void testGetSumOfDigits() {
  int input;

  std::cout << "Enter a Number: ";
  std::cin >> input;

  int result = getSumOfDigits(input);
  std::cout << "Total Sum of Digits: " << result << std::endl;
}

void testStartsWith() {
  std::string userInput;
  std::string userPrefix;

  std::cout << "Enter a Number: ";
  std::cin >> userInput;

  std::cout << "Enter a Prefix: ";
  std::cin >> userPrefix;

  bool result = startsWith(userInput, userPrefix);
  std::cout << "Does the number start with the Prefix? "
            << (result ? "True" : "False") << std::endl;
}

void testHasValidPrefix() {
  std::string userInput;

  std::cout << "Enter a Prefix: ";
  std::cin >> userInput;

  if (hasValidPrefix(userInput)) {
    std::cout << "True" << std::endl;
  } else {
    std::cout << "False" << std::endl;
  }
}

void testSumming() {
  std::string userInput;

  std::cout << "Enter a Card Number: ";
  std::cin >> userInput;

  int totalSum = sumOfOddDigitsRightToLeft(userInput) +
                 sumOfEvenDigitsRightToLeft(userInput);

  std::cout << "Total Sum: " << totalSum << std::endl;
}

void areWeTesting() {
  std::string userInput;

  std::cout << "Do you want to test getSumOfDigits()? ";
  std::cin >> userInput;

  if (userInput == "yes" || userInput == "y") {
    testGetSumOfDigits();
  }

  std::cout << "Do you want to test startsWith()? ";
  std::cin >> userInput;

  if (userInput == "yes" || userInput == "y") {
    testStartsWith();
  }

  std::cout << "Do you want to test hasValidPrefix()? ";
  std::cin >> userInput;

  if (userInput == "yes" || userInput == "y") {
    testStartsWith();
  }

  std::cout << "Do you want to test Odd & Even Summing? ";
  std::cin >> userInput;

  if (userInput == "yes" || userInput == "y") {
    testSumming();
  }
}
