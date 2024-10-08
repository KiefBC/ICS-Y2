#include "Credit.h"

int getSumOfDigits(int number) {
  int sum = Constants::ZERO;

  while (number > Constants::ZERO) {
    int lastDigit = number % Constants::TEN;
    sum += lastDigit;
    number /= Constants::TEN;
  }

  return sum;
}

bool startsWith(const std::string cardNumber, const std::string prefix) {
  const std::string substr =
      cardNumber.substr(Constants::START_INDEX, prefix.length());

  return substr == prefix;
}

bool hasValidPrefix(const std::string &cardNumber) {
  for (const auto prefix : Constants::cardPrefix) {
    if (startsWith(cardNumber, prefix)) {
      return true;
    }
  }

  return false;
}

int sumOfOddDigitsRightToLeft(const std::string cardNumber) {
  int sum = Constants::ZERO;

  for (int i = cardNumber.size() - 1; i >= 0; i--) {
    int digitOnRight = cardNumber.size() - i;

    if (digitOnRight % 2 != Constants::ZERO) {
      int digit = cardNumber[i] - '0';
      sum += digit;
    }
  }

  return sum;
}

int sumOfEvenDigitsRightToLeft(const std::string cardNumber) {
  int sum = 0;

  for (int i = cardNumber.size() - 1; i >= 0; i--) {
    int digitOnRight = cardNumber.size() - i;

    if (digitOnRight % 2 == 0) {
      // Fancy trick for converting String to Int
      int digit = cardNumber[i] - '0';
      int doubledValue = digit * Constants::TWO;

      sum += getSumOfDigits(doubledValue);
    }
  }

  return sum;
}

bool isCardValid(const std::string &cardNumber) {
  const int CARD_SIZE = cardNumber.size();
  bool valid = true;
  const int cardNumberWidth = 20;
  const int statusWidth = 10;

  if (CARD_SIZE < 13 || CARD_SIZE > 16) {
    valid = false;
  }

  if (!hasValidPrefix(cardNumber)) {
    valid = false;
  }

  int totalSum = sumOfOddDigitsRightToLeft(cardNumber) +
                 sumOfEvenDigitsRightToLeft(cardNumber);

  if (totalSum % 10 != 0) {
    valid = false;
  }

  if (valid) {
    std::cout << std::setw(cardNumberWidth) << cardNumber
              << std::setw(statusWidth) << "Valid:1" << std::endl;
    return true;
  }

  std::cout << std::setw(cardNumberWidth) << cardNumber
            << std::setw(statusWidth) << "Invalid:0" << std::endl;
  return false;
}
