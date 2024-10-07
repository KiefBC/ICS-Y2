#include "Credit.h"

/*
 * This takes in a given number and adds up all the digits.
 * It then returns the total as an <int> type
 */
int getSumOfDigits(int number) {
  int sum = 0;

  while (number > 0) {
    int lastDigit = number % 10;
    sum += lastDigit;

    std::cout << "lastDigit: " << lastDigit << std::endl;
    number /= 10;
  }

  return sum;
}

/*
 * This checks if our cardNumber starts with the given Prefix
 */
bool startsWith(const std::string cardNumber, const std::string prefix) {
  // We are only interested in the first digit of the cardNumber
  const std::string substr =
      cardNumber.substr(Constants::START_INDEX, Constants::END_INDEX);

  return substr == prefix;
}

/*
 * This Checks if our cardNumber starts with one of the Literals in
 * Constants::cardPrefix
 */
bool hasValidPrefix(const std::string &cardNumber) {
  // We only need the first digit of the cardNumber
  const std::string substr =
      cardNumber.substr(Constants::START_INDEX, Constants::END_INDEX);

  for (const auto prefix : Constants::cardPrefix) {
    if (substr == prefix) {
      return true;
    }
  }

  return false;
}
