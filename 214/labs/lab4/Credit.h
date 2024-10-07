#ifndef CREDIT_H
#define CREDIT_H

#include <iostream>
#include <vector>

int getSumOfDigits(int);
bool startsWith(const std::string, const std::string);
bool hasValidPrefix(const std::string&);

namespace Constants {
  const std::vector<std::string> cardPrefix = {"4", "5", "6", "37"};
  const int START_INDEX = 0;
  const int END_INDEX = 1;
}

#endif
