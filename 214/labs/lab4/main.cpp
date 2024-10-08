#include "Credit.h"
#include "test.h"

int main() {
  std::string userInput;
  int validSum = Constants::ZERO;
  int invalidSum = Constants::ZERO;

  std::cout << "Are we Testing? ";
  std::cin >> userInput;
  std::cout << "" << std::endl;

  if (userInput == "y" || userInput == "yes") {
    areWeTesting();
  }

  std::string filename = "cards.txt";
  std::ifstream fin;
  fin.open(filename);

  if (fin.is_open()) {
    std::string ccNum;

    while (fin >> ccNum) {
      if (isCardValid(ccNum)) {
        validSum++;
      } else {
        invalidSum++;
      }
    }

    fin.close();

    std::cout << "\nTotal Valid: " << validSum << std::endl;
    std::cout << "Total Invalid: " << invalidSum << std::endl;
  } else {
    std::cout << "Failed to open file: \"" << filename << "\"" << std::endl;
    exit(1);
  }

  return 0;
}
