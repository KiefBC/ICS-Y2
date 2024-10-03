//
// Created by kiefer on 10/2/24.
//
#include "Card.h"
#include <iomanip>

int main()
{
    srand(time(0));

    int totalCardsDrawn = 0;
    int totalTrials = 0;
    int loopSize = 10000000;

    bool verbose = false;
    for (int i = 0; i < loopSize; i++)
    {
        int pickCount = getPickCountNeededForFourSuits(verbose);
        totalCardsDrawn += pickCount;
        totalTrials++;
    }

    double averageCardsDrawn = static_cast<double>(totalCardsDrawn) / totalTrials;
    std::cout << "\nTotal cards drawn: " << totalCardsDrawn << std::endl;
    std::cout << "Average cards drawn: " << averageCardsDrawn << std::endl;

    return 0;
}



