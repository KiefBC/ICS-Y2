#include "Card.h"

int pickRandomCard()
{
    return rand() % Constants::CARD_COUNT;
}

// Get the rank of a specific card index
// - param 1: an int representing the card index
// - return: an enum representing the Rank of the card index given.
// getRank();
Rank getRank(int cardIndex)
{
    return static_cast<Rank>(cardIndex % Constants::NUM_RANKS);
}

// Get the suit of a specific card index
// - param 1: an int representing the card index
// - return: an enum representing the Suit of the card index given.
// getSuit();
Suit getSuit(int cardIndex)
{
    return static_cast<Suit>(cardIndex / Constants::NUM_RANKS);
}

// A function to assess whether all elements in a boolean array are true
// You can use this function to determine whether all suits have been picked.
// - param 1: an array of boolean values(decide if it should be const or not)
// - param 2: ? do we need any other parameters here to make this work? You decide.
// - return: a bool : true if ALL the elements in param 1 are true, false otherwise.
// allArrayElementsAreTrue();
bool allArrayElementsAreTrue(const bool suitsPicked[])
{
    for (int i = 0; i < Constants::NUM_SUITS; i++)
    {
        if (!suitsPicked[i])
        {
            return false;
        }
    }

    return true;
}

// This is the function that does all the work behind solving the problem (including
// sending output to the console).
// This function should create/use an array of Boolean values (all initially false)
// to represent the suits that have been picked.
// It should make use of allArrayElementsAreTrue() to test if all suits have been
// picked.
// - param 1: a bool called “verbose” (meaning wordy) that defaults to true.
// If verbose is true, generate output cards picked & the pick count.
// - return: an int representing the number of card picks it takes to cover 4 suits.
// getPickCountNeededForFourSuits();
int getPickCountNeededForFourSuits(bool verbose)
{
    bool suitsPicked[Constants::NUM_SUITS] = {false, false, false, false};
    int pickCount = 0;

    while (!allArrayElementsAreTrue(suitsPicked))
    {
        int cardIndex = pickRandomCard();
        Suit suit = getSuit(cardIndex);

        if (!suitsPicked[static_cast<int>(suit)])
        {
            suitsPicked[static_cast<int>(suit)] = true;

            if (verbose)
            {
                std::cout << "Picked card: " << Constants::RANKS[static_cast<int>(getRank(cardIndex))] << " of " << Constants::SUITS[static_cast<int>(suit)] << std::endl;
            }
        }

        pickCount++;
    }

    if (verbose)
    {
        std::cout << "Picks needed to get all suits: " << pickCount << std::endl;
    }

    return pickCount;
}