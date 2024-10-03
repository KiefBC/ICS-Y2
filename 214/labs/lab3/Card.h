//
// Created by kiefer on 10/2/24.
//

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

enum class Suit
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
    count,
};

enum class Rank
{
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
    count,
};

namespace Constants
{
    constexpr int CARD_COUNT{static_cast<int>(Rank::count) * static_cast<int>(Suit::count)}; // the # of cards in a deck
    constexpr int NUM_RANKS{static_cast<int>(Rank::count)}; // the # of ranks in a deck
    constexpr int NUM_SUITS{static_cast<int>(Suit::count)}; // the # of suits in a deck

    /*
     * Potentially both of these work, but I'm not sure which is better
     */
    // const std::string SUITS[]{"CLUBS", "DIAMONDS", "HEARTS", "SPADES"}; // initialize & match with enums
    // const std::string RANKS[]{
    //     "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE"
    // };
    constexpr const char* SUITS[]{"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
    constexpr const char* RANKS[]{
        "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE"
    };
};

int pickRandomCard();
Rank getRank(int);
Suit getSuit(int);
bool allArrayElementsAreTrue(const bool array[]);
int getPickCountNeededForFourSuits1(bool, std::mt19937&);
int getPickCountNeededForFourSuits3(bool);
int getPickCountNeededForFourSuits(bool);

#endif // CARDS_H
