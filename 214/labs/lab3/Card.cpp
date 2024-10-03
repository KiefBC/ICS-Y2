#include "Card.h"

int pickRandomCard()
{
    return rand() % Constants::CARD_COUNT;
}

Rank getRank(int cardIndex)
{
    return static_cast<Rank>(cardIndex % Constants::NUM_RANKS);
}

Suit getSuit(int cardIndex)
{
    return static_cast<Suit>(cardIndex / Constants::NUM_RANKS);
}

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

int getPickCountNeededForFourSuits(bool verbose)
{
    int suitsPickedMask = 0;
    constexpr int allSuitsMask = 0b1111; // All suits picked when mask is 1111
    int pickCount = 0;

    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, 3);

    while (suitsPickedMask != allSuitsMask)
    {
        const int suit = distribution(generator);
        const int suitBit = 1 << suit;

        if (!(suitsPickedMask & suitBit))
        {
            suitsPickedMask |= suitBit;

            if (verbose)
            {
                std::cout << "Picked suit: " << Constants::SUITS[suit] << std::endl;
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