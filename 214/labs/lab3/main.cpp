//
// Created by kiefer on 10/2/24.
//
#include "Card.h"

int main()
{
    srand(time(0));

    int card = pickRandomCard();
    std::cout << "Card Index: " << card << std::endl;

    Rank rank = getRank(card);
    std::cout << "Rank: " << Constants::RANKS[static_cast<int>(rank)] << std::endl;

    Suit suit = getSuit(card);
    std::cout << "Suit: " << Constants::SUITS[static_cast<int>(suit)] << std::endl;

    const bool verbose = false;
    int pickCount = getPickCountNeededForFourSuits(verbose);
    std::cout << "Pick Count: " << pickCount << std::endl;

    return 0;
}