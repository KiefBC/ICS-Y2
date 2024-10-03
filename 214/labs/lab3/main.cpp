//
// Created by kiefer on 10/2/24.
//
#include "Card.h"
#include <iomanip>

int main() {
    thread_local std::mt19937 generator(std::random_device{}());
    const auto startTime = std::chrono::high_resolution_clock::now();

    int totalCardsDrawn = 0;
    int totalCardsDrawn2 = 0;
    int totalTrials = 0;
    int totalTrials2 = 0;
    constexpr int loopSize = 100000000;

    std::cout << "\nStarting first simulation..." << std::endl;
    for (int i = 0; i < loopSize; i++) {
        constexpr bool verbose = false;
        const int pickCount = getPickCountNeededForFourSuits1(verbose, generator);
        totalCardsDrawn += pickCount;
        totalTrials++;
    }

    const double averageCardsDrawn = static_cast<double>(totalCardsDrawn) / totalTrials;
    std::cout << "\nTotal cards drawn: " << totalCardsDrawn << std::endl;
    std::cout << "Average cards drawn: " << averageCardsDrawn << std::endl;

    auto endTime1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime1 - startTime);
    std::cout << "Time taken for simulation: " << duration1.count() / 60000 << " minutes "
              << (duration1.count() % 60000) / 1000 << " seconds" << std::endl;

    std::cout << "\nStarting second simulation..." << std::endl;
    const auto startTime2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < loopSize; i++) {
        constexpr bool verbose = false;
        int pickCount2 = getPickCountNeededForFourSuits(verbose);
        totalCardsDrawn2 += pickCount2;
        totalTrials2++;
    }

    const double averageCardsDrawn2 = static_cast<double>(totalCardsDrawn2) / totalTrials2;
    std::cout << "\nTotal cards drawn: " << totalCardsDrawn2 << std::endl;
    std::cout << "Average cards drawn: " << averageCardsDrawn2 << std::endl;

    auto endTime2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime2 - startTime2);
    std::cout << "Time taken for simulation: " << duration2.count() / 60000 << " minutes "
              << (duration2.count() % 60000) / 1000 << " seconds" << std::endl;

}



