//
// Created by kiefer on 9/25/24.
//

#ifndef LAB2_THOMASSAIDSO_H
#define LAB2_THOMASSAIDSO_H
#include <string>


/**
 * Handles input for days, months, and years.
 * @param min Minimum value for input.
 * @param max Maximum value for input.
 * @param prompt Message to prompt the user.
 * @param errorMessage Message to display on invalid input.
 * @return Validated input within the specified range.
 */
int validateInput(int min, int max, const std::string& prompt, const std::string& errorMessage);


#endif //LAB2_THOMASSAIDSO_H
