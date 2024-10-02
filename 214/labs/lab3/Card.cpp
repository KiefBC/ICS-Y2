//
// Created by kiefer on 10/2/24.
//
#include "Card.h"

// Picks a random card from the deck (represented by an int between 0-51)
// - params: none
// - return: an int between 0 - 51
int pickRandomCard() {
    return rand() % Constants::CARD_COUNT;
}

// Gets the rank of a specific card index
// - param 1: an int representing the card index
// - return: an enum representing the Rank of the card index given.
Rank getRank(int cardIndex) {
    int rankValue = cardIndex % static_cast<int>(Rank::count);
    return static_cast<Rank>(rankValue);
}

// Gets the suit of a specific card index
// - param 1: an int representing the card index
// - return: an enum representing the Suit of the card index given.
Suit getSuit(int cardIndex) {
    int suitValue = cardIndex / static_cast<int>(Rank::count);
    return static_cast<Suit>(suitValue);
}

// Checks if all elements in a boolean array are true
// - param 1: an array of boolean values
// - param 2: the size of the array
// - return: true if all elements are true, false otherwise.
bool allArrayElementsAreTrue(const bool arr[], int size) {
    for (int i = 0; i < size; ++i) {
        if (!arr[i]) {
            return false;
        }
    }
    return true;
}

// Calculates the number of picks needed to get all four suits
// - param 1: a bool called "verbose" that defaults to true.
//            If verbose is true, outputs cards picked & the pick count.
// - return: an int representing the number of card picks it takes to cover 4 suits.
int getPickCountNeededForFourSuits(bool verbose) {
    bool suitsPicked[static_cast<int>(Suit::count)] = {false};
    int pickCount = 0;

    while (!allArrayElementsAreTrue(suitsPicked, static_cast<int>(Suit::count))) {
        int cardIndex = pickRandomCard();
        Rank rank = getRank(cardIndex);
        Suit suit = getSuit(cardIndex);

        suitsPicked[static_cast<int>(suit)] = true;
        ++pickCount;

        if (verbose) {
            std::cout << "Pick " << pickCount << ": "
                      << Constants::RANKS[static_cast<int>(rank)] << " of "
                      << Constants::SUITS[static_cast<int>(suit)] << std::endl;
        }
    }

    if (verbose) {
        std::cout << "Total picks needed: " << pickCount << std::endl;
    }

    return pickCount;
}

// Shuffles the deck
void shuffleDeck(int deck[], int size) {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the deck
    std::shuffle(deck, deck + size, gen);

    // Print the shuffled deck
//    for (int i = 0; i < size; ++i) {
//        std::cout << deck[i] << " " << std::endl;
//    }
}

int getPickCountNeededForFourSuitsNoReplacement(bool verbose) {
    bool suitsPicked[static_cast<int>(Suit::count)] = {false};
    int pickCount = 0;

    int deck[Constants::CARD_COUNT];
    for (int i = 0; i < Constants::CARD_COUNT; ++i) {
        deck[i] = i;
    }

    shuffleDeck(deck, Constants::CARD_COUNT);
    int currentCardIndex = 0;

    // Draw cards from the deck until all suits have been picked or deck is empty
    while (!allArrayElementsAreTrue(suitsPicked, static_cast<int>(Suit::count)) &&
           currentCardIndex < Constants::CARD_COUNT) {
        int cardIndex = deck[currentCardIndex];
        Rank rank = getRank(cardIndex);
        Suit suit = getSuit(cardIndex);

        suitsPicked[static_cast<int>(suit)] = true;
        ++pickCount;
        ++currentCardIndex;

        if (verbose) {
            std::cout << "Pick " << pickCount << ": "
                      << Constants::RANKS[static_cast<int>(rank)] << " of "
                      << Constants::SUITS[static_cast<int>(suit)] << std::endl;
        }
    }

    if (verbose) {
        std::cout << "Total picks needed (without replacement): " << pickCount << std::endl;
    }

    return pickCount;
}
