//
// Created by kiefer on 9/23/24.
//

#include "Zellers.h"
#include "ThomasSaidSo.h"
#include <iostream>
#include <limits>

Weekday calculateWeekday(int year, int month, int day) {

    /*
    * This handles the case where the month is January or February
    * 1 becomes 13 and 2 becomes 14
    * We also decrement the year by 1 because we are treating January and February as months of the previous year
    */
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }

    int yearOfCentury = year % 100;
    int century = year / 100;

    int dayOfWeek = (day + (13 * (month + 1)) / 5 + yearOfCentury + yearOfCentury / 4 + century / 4 + 5 * century) % 7;

    switch (dayOfWeek) {
        case 0:
            return Weekday::Saturday;
        case 1:
            return Weekday::Sunday;
        case 2:
            return Weekday::Monday;
        case 3:
            return Weekday::Tuesday;
        case 4:
            return Weekday::Wednesday;
        case 5:
            return Weekday::Thursday;
        case 6:
            return Weekday::Friday;
        default:
            return Weekday::Saturday;
    }
}

int promptForYear() {
    int yearInput;

    std::cout << "Enter the year (ex: 1990): ";
    yearInput = validateInput(0, std::numeric_limits<int>::max(), "Enter the year (ex: 1990): ", "Invalid input. Please enter a valid year: ");

    if (yearInput == -0) {
        yearInput = 0;
    }

    return yearInput;
}

int promptForMonth() {
    int monthInput;

    std::cout << "Enter the month (ex: 8): ";
    monthInput = validateInput(1, 12, "Enter the month (ex: 8): ", "Invalid input. Please enter a valid month between 1 and 12: ");

    return monthInput;
}

int promptForDay(int month, int year) {
    // TODO: Potentially change daysOfMonth to something more descriptive
    int dayInput;
    int daysOfMonth;

    // Covering for months with 30 days, 28 days, and 31 days
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            daysOfMonth = 30;
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                daysOfMonth = 29; // Leap year
            } else {
                daysOfMonth = 28; // Non-leap year
            }
            break;
        default:
            daysOfMonth = 31;
            break;
    }

    std::cout << "Enter the day (max " << daysOfMonth << "): ";
    dayInput = validateInput(1, daysOfMonth, "Enter the day (max " + std::to_string(daysOfMonth) + "): ", "Invalid input. Please enter a valid day between 1 and " + std::to_string(daysOfMonth) + ": ");

    return dayInput;
}