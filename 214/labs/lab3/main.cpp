//
// Created by kiefer on 10/2/24.
//
#include "Card.h"
#include <iomanip>

int main()
{
    srand(time(0));

    auto startTime = std::chrono::high_resolution_clock::now();


    int totalCardsDrawn = 0;
    int totalTrials = 0;
    int loopSize = 100000000;

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

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Time taken for simulation: " << duration.count() / 60000 << " minutes " << (duration.count() % 60000) / 1000 << " seconds" << std::endl;

    return 0;
}



