//
// Created by kiefer on 10/2/24.
//
#include "Card.h"

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Variables to keep track of total cards drawn and total trials
    long long totalCardsDrawn = 0;
    long long totalTrials = 0;
    int loopSize = 10000000;

    // Loop for the specified number of trials
    for (int i = 0; i < loopSize; ++i) {
        int picksNeeded = getPickCountNeededForFourSuitsNoReplacement(false); // Set verbose to false
        totalCardsDrawn += picksNeeded;
        ++totalTrials;
    }

    // Calculate the average number of picks needed
    double averagePicks = static_cast<double>(totalCardsDrawn) / totalTrials;

    // Output the result
    std::cout << "After " << totalTrials << " trials (without replacement), the average number of picks needed to get all four suits is: "
              << averagePicks << std::endl;

    return 0;
}
