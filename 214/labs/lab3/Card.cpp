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

int getPickCountNeededForFourSuits3(bool verbose)
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

int getPickCountNeededForFourSuits1(bool verbose, std::mt19937 &generator)
{
    int cardSuitPickedMask = 0;
    constexpr int allCardsPicked = 0b1111;
    int pickCount = 0;

    std::uniform_int_distribution<> distribution(0, 3);

    while (cardSuitPickedMask != allCardsPicked)
    {
        const int cardSuit = distribution(generator);
        const int cardSuitBit = 1 << cardSuit;

        if (!(cardSuitPickedMask & cardSuitBit))
        {
            cardSuitPickedMask |= cardSuitBit;

            if (verbose)
            {
                std::cout << "Picked cardSuit: " << Constants::SUITS[cardSuit] << " " << Constants::RANKS[cardSuit] << std::endl;
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

int getPickCountNeededForFourSuits(bool verbose)
{
    std::vector<int> deck(52);
    for (int i = 0; i < 52; ++i)
        deck[i] = i;

    thread_local std::mt19937 generator(std::random_device{}());
    std::shuffle(deck.begin(), deck.end(), generator);

    bool suitsPicked[Constants::NUM_SUITS] = {false, false, false, false};
    int pickCount = 0;

    for (int cardIndex : deck)
    {
        Suit suit = getSuit(cardIndex);

        if (!suitsPicked[static_cast<int>(suit)])
        {
            suitsPicked[static_cast<int>(suit)] = true;

            if (verbose)
            {
                std::cout << "Picked card: " << Constants::RANKS[static_cast<int>(getRank(cardIndex))] << " of "
                          << Constants::SUITS[static_cast<int>(suit)] << std::endl;
            }
        }

        pickCount++;

        if (allArrayElementsAreTrue(suitsPicked))
            break;
    }

    if (verbose)
    {
        std::cout << "Picks needed to get all suits: " << pickCount << std::endl;
    }

    return pickCount;
}