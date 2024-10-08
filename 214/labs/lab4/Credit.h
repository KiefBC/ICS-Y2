#ifndef CREDIT_H
#define CREDIT_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

/**
 * @brief Calculates the Sum of a Number
 *
 * This function takes in a Number and it will take every digit of that number
 * and sum them all together.
 *
 * @param number A number
 *
 * @return Returns the Sum
 */
int getSumOfDigits(int);

/**
 * @brief - Checks if a String begins with a specific Prefix
 *
 * This function will take in a std::string number and a std::string prefix and
 * will check if the number begins with the prefix.
 *
 * @param cardNumber Credit Card Number
 * @param prefix Beginning Prefix
 */
bool startsWith(const std::string, const std::string);

/**
 * @brief Checks if a card number has a valid prefix.
 *
 * This function determines if the provided credit card number starts with one
 * of the valid prefixes defined in the system (e.g., "4", "5", "6", or "37").
 *
 * @param cardNumber The credit card number to check.
 *
 * @return Returns true if the card number has a valid prefix; otherwise,
 * returns false.
 */
bool hasValidPrefix(const std::string &);

/**
 * @brief Sums the digits at odd positions from right to left in a card number.
 *
 * This function calculates the sum of the digits that are in the odd positions
 * when counting from right to left in the provided card number string.
 *
 * @param cardNumber The credit card number as a string.
 *
 * @return The sum of the digits at odd positions from right to left.
 */
int sumOfOddDigitsRightToLeft(const std::string);

/**
 * @brief Sums the processed digits at even positions from right to left in a
 * card number.
 *
 * This function calculates the sum of the digits that are in the even positions
 * when counting from right to left in the provided card number string. Each
 * digit is doubled, and if the result is a two-digit number, its digits are
 * added together before summing.
 *
 * @param cardNumber The credit card number as a string.
 *
 * @return The sum of the processed digits at even positions from right to left.
 */
int sumOfEvenDigitsRightToLeft(const std::string);

/**
 * @brief Validates a credit card number using the Luhn algorithm.
 *
 * This function checks if a credit card number is valid based on the following
 * criteria:
 * - The number must be between 13 and 16 digits long.
 * - It must start with a valid prefix.
 * - The sum of the digits, processed according to the Luhn algorithm, must be
 * divisible by 10.
 *
 * @param cardNumber The credit card number to validate.
 *
 * @return Returns true if the card number is valid; otherwise, returns false.
 */
bool isCardValid(const std::string &);

namespace Constants {
const std::vector<std::string> cardPrefix = {"4", "5", "6", "37"};
const int START_INDEX = 0;
const int ZERO = 0;
const int TEN = 10;
const int TWO = 2;
} // namespace Constants

#endif
