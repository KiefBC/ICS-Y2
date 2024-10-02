//
// Created by kiefer on 10/2/24.
//
#include "Card.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int picksNeeded = getPickCountNeededForFourSuits();

    std::cout << "Number of picks needed to get all four suits: " << picksNeeded << std::endl;

    return 0;
}
