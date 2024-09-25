//
// Created by kiefer on 9/19/24.
//

#include <iostream>
#include "Testing.h"

int test() {
    int x { 5 };
    std::cout << "x is: " << *&x << std::endl;

    int arr[] = { 1, 2, 3, 4, 5 };
    std::cout << "arr is: " << *arr << std::endl; // Gets first element
    std::cout << "arr is: " << *(arr + 1) << std::endl; // Gets second element

    // Demonstrate the use of pointers by passing them to functions
    int y;
    int* pX = nullptr;

    if (pX) {
        std::cout << pX << std::endl;
    }

    pX = &y;

    std::cout << pX << std::endl; // Prints the memory address of y
}

int add(int *a, int *b) {
    return *a + *b;
}