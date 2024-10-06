#include <iostream>

int main() {
  int cardNumber, tempCardNumber, evenPositionSum = 0, oddPositionSum = 0, positionCounter = 0, currentDigit, totalSum = 0;
  
  std::cout << "Enter a card number: ";
  std::cin >> cardNumber;

  while (cardNumber < 1) {
    std::cout << "Invalid card number. Please enter a number between 1 and 52: ";
    std::cin >> cardNumber;
  }
 
  tempCardNumber = cardNumber;

  while (tempCardNumber > 0) {
    cardValue = tempCardNumber % 10;

    if (positionCounter % 2 == 0) {
      currentDigit *= 2;
      if (currentDigit > 9) {
        currentDigit = (currentDigit / 10) + (currentDigit % 10);
      }
    }
    sum += cardValue;
    tempCardNumber /= 10;
  }

  std::cout << "The sum of the digits in " << cardNumber << " is " << sum << std::endl;

}
