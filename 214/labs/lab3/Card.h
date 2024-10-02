//
// Created by kiefer on 10/2/24.
//

#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

// Enums and Constants (as previously defined)
enum class Suit {
    Hearts,
    Diamonds,
    Clubs,
    Spades,
    count
};

enum class Rank {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    count
};

namespace Constants {
    const int CARD_COUNT = static_cast<int>(Suit::count) * static_cast<int>(Rank::count);
    const int NUM_SUITS = static_cast<int>(Suit::count);
    const int NUM_RANKS = static_cast<int>(Rank::count);
//    constexpr int CARD_COUNT{ static_cast<int>(Suit::count) * static_cast<int>(Rank::count) };
    const std::string SUITS[] { "Hearts", "Diamonds", "Clubs", "Spades" };
    const std::string RANKS[] { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                                "Ten", "Jack", "Queen", "King", "Ace" };
}

// Shuffles the deck
void shuffleDeck(int deck[], int size);

// Calculates the number of picks needed to get all four suits without replacement
int getPickCountNeededForFourSuitsNoReplacement(bool verbose = true);

// Picks a random card from the deck (represented by an int between 0-51)
int pickRandomCard();

// Gets the rank of a specific card index
Rank getRank(int cardIndex);

// Gets the suit of a specific card index
Suit getSuit(int cardIndex);

// Checks if all elements in a boolean array are true
bool allArrayElementsAreTrue(const bool arr[], int size);

// Calculates the number of picks needed to get all four suits
int getPickCountNeededForFourSuits(bool verbose = true);

#endif // CARDS_H
