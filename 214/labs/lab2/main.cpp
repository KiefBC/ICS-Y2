//
// Created by kiefer on 9/23/24.
//

#include <iostream>
#include "main.h"
#include "Zellers.h"

int main()
{
    int year = promptForYear();
    int month = promptForMonth();
    int day = promptForDay(month, year);

    Weekday weekday = calculateWeekday(year, month, day);

//    switch (weekday) {
//        case Weekday::Saturday:
//            std::cout << "The day of the week is Saturday." << std::endl;
//            break;
//        case Weekday::Sunday:
//            std::cout << "The day of the week is Sunday." << std::endl;
//            break;
//        case Weekday::Monday:
//            std::cout << "The day of the week is Monday." << std::endl;
//            break;
//        case Weekday::Tuesday:
//            std::cout << "The day of the week is Tuesday." << std::endl;
//            break;
//        case Weekday::Wednesday:
//            std::cout << "The day of the week is Wednesday." << std::endl;
//            break;
//        case Weekday::Thursday:
//            std::cout << "The day of the week is Thursday." << std::endl;
//            break;
//        case Weekday::Friday:
//            std::cout << "The day of the week is Friday." << std::endl;
//            break;
//    }

    std::string dayOfWeek[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    std::cout << "The day of the week is " << dayOfWeek[static_cast<int>(weekday)] << "." << std::endl;
}
