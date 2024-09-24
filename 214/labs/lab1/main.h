//
// Created by kiefer on 11/09/24.
//

#ifndef MAIN_H
#define MAIN_H

bool userGuess(int maxRange);

int promptUserForMaxRange();

int pickRanNumInRange(int minRange, int maxRange);

bool userPlayAgain();

int promptUserForGuess(int minRange, int maxRange);

void welcomeMsg();

void playOneRound();

void goodbyeMsg(long duration);

#endif //MAIN_H
