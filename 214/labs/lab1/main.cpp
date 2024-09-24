#include <iostream>
#include <limits> // For numeric_limits
#include <sstream> // For converting input Str -> int
#include <string> // For String
#include <chrono> // For our timer
#include "main.h" // For our function prototypes

using namespace std; // I hate typing std:: before everything

int main() {
    // Start your engines.... I mean, the game
    const auto start = chrono::high_resolution_clock::now();

    bool playAgain = true;
    while (playAgain) {
        playOneRound();
        playAgain = userPlayAgain();
    }

    // Calculate the time it took you to play the game
    const auto end = chrono::high_resolution_clock::now();
    const auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();
    goodbyeMsg(duration);
}

// This will be the main function that will run the game
void playOneRound() {
    constexpr int minRange = 0; // Placeholder for now
    welcomeMsg();

    int guessCount = 0;
    bool correct = false;
    const int maxRange = promptUserForMaxRange();
    const int mysteryNumber = pickRanNumInRange(minRange, maxRange);

    while (!correct) {
        if (const int userGuess = promptUserForGuess(minRange, maxRange); userGuess < mysteryNumber) {
            cout << "Too low!\n" << endl;
        } else if (userGuess > mysteryNumber) {
            cout << "Too high!\n" << endl;
        } else {
            correct = true;
        }

        guessCount++;
    }

    cout << "Correct! It took you " << guessCount << " guesses!\n" << endl;
}

// This function will prompt the user for the maximum range
int promptUserForMaxRange() {
    string userInput;
    int maxRange = 0;

    while (true) {
        cout << "Enter the Maximum Range: ";
        getline(cin, userInput); // Take input as a string

        // Convert the input string to an integer
        if (stringstream ss(userInput); ss >> maxRange && ss.eof()) {
            if (maxRange < 0) {
                cout << "Please enter a positive number.\n" << endl;
            } else {
                return maxRange;
            }
        } else {
            cout << "Invalid input. Please enter a valid number.\n" << endl;
        }
    }
}

// This function will generate a random number within the range
int pickRanNumInRange(const int minRange, const int maxRange) {
    srand(time(0)); // LSP gives me errors about this not being "random" enough

    const int mysteryNumber = minRange + rand() % (maxRange - minRange + 1);
    cout << "Mystery Number: " << mysteryNumber << endl;

    return mysteryNumber;
}

// This function will prompt the user for their guess
int promptUserForGuess(const int minRange, const int maxRange) {
    string input;
    int userGuess = 0;

    while (true) {
        cout << "Enter your guess between " << minRange << " and " << maxRange << ": ";
        getline(cin, input); // Take input as a string

        // Convert the input string to an integer
        if (stringstream ss(input); ss >> userGuess && ss.eof()) {
            if (userGuess < minRange || userGuess > maxRange) {
                cout << "Please enter a number between " << minRange << " and " << maxRange << ".\n";
            } else {
                return userGuess;
            }
        } else {
            cout << "Invalid input. Please enter a valid integer.\n" << endl;
        }
    }
}

// This function will allow the user to play again
bool userPlayAgain() {
    char response;

    while (true) {
        cout << "Do you want to play again? (y/n): ";
        cin >> response;

        if (tolower(response) == 'y') {


            cout << endl;
            return true;
        }
        if (tolower(response) == 'n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return false;
        }

        cout << "Invalid input. Please enter 'y' or 'n'.\n" << endl;
    }
}

// This function will display the welcome message
void welcomeMsg() {
    cout << "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*" << endl;
    cout << " Welcome to the Number Guessing Game!" << endl; // Leading whitespace intended
    cout << "  Written by Kiefer Hay, 09/11/2024" << endl; // Leading whitespace intended
    cout << "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n" << endl;
}

// This function will display the goodbye message
void goodbyeMsg(const long duration) {
    cout << "\n*=*=*=*=*=*=*=*=*=*=*=*" << endl;
    cout << "       Goodbye!" << endl; // Leading whitespace intended
    cout << "You played for " << duration << " seconds." << endl; // Leading whitespace intended
    cout << "*=*=*=*=*=*=*=*=*=*=*=*" << endl;
}
