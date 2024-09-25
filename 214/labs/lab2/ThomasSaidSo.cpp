//
// Created by kiefer on 9/25/24.
//

#include "ThomasSaidSo.h"
#include <iostream>
#include <limits>

int validateInput(int min, int max, const std::string &prompt, const std::string &errorMessage) {
    int input;
    std::cout << prompt;
    std::cin >> input;

    while (std::cin.fail() || input < min || input > max) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << errorMessage;
        std::cin >> input;
    }

    return input;
}