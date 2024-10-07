#include "Credit.h"

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

bool startsWith(const std::string cardNumber, const std::string prefix) {
  // We are only interested in the first digit of the cardNumber
  const std::string substr = cardNumber.substr(Constants::START_INDEX, Constants::END_INDEX);

  return substr == prefix; 
}

bool hasValidPrefix(const std::string& cardNumber) {
  std::string substr = cardNumber.substr(Constants::START_INDEX, Constants::END_INDEX);
  
  for (const auto prefix : Constants::cardPrefix) {
    if (substr == prefix) {
      return true;
    }
  }

  return false;
}
