//
// Created by kiefer on 9/23/24.
//

#ifndef ZELLERS_H
#define ZELLERS_H

/**
 * @brief Enum class for the days of the week
 *
 * This enum class is used to represent the days of the week
 */
enum class Weekday {
    Saturday,
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday
};

/**
 * @brief Prompts the user for a year and returns the year
 *
 * This function will prompt the user for a year and return the year between 0 and 9999
 * @return the year
 */
int promptForYear();

/**
 * @brief Prompts the user for a month and returns the month
 *
 * This function will prompt the user for a month and return the month between 1 and 12
 * @return the month
 */
int promptForMonth();

/**
 * @brief Prompts the user for a day and returns the day
 *
 * This function will prompt the user for a day and return the day between 1 and 31
 * @param month the month that the day is in
 * @param year the year that the day is in
 * @return the day
 */
int promptForDay(int month, int year);

/**
 * @brief Calculates the day of the week for a given date
 *
 * This function will calculate the day of the week for a given date
 * @param year user inputted year
 * @param month user inputted month
 * @param day user inputted day
 * @return the day of the week
 */
Weekday calculateWeekday(int year, int month, int day);


#endif //ZELLERS_H
