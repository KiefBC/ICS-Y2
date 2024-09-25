//
// Created by kiefer on 9/23/24.
//

#include <iostream>
#include "main.h"
#include "Zellers.h"

int main() {
    std::cout << "===========================" << std::endl;
    std::cout << "Test run data: 2015, 1, 25" << std::endl;
    std::cout << "---------------------------" << std::endl;
    Weekday test = calculateWeekday(2015, 1, 25);
    std::string dayOfWeek_test[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    std::cout << "     Test run: " << dayOfWeek_test[static_cast<int>(test)] << std::endl;
    std::cout << "===========================\n" << std::endl;

    int year = promptForYear();
    int month = promptForMonth();
    int day = promptForDay(month, year);

    Weekday weekday = calculateWeekday(year, month, day);

    std::string dayOfWeek[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    std::cout << "\n================================" << std::endl;
    std::cout << "The day of the week is " << dayOfWeek[static_cast<int>(weekday)] << "." << std::endl;
    std::cout << "================================" << std::endl;
}