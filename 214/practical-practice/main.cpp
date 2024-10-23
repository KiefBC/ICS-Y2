#include <array>
#include <iostream>
#include <unordered_map>

int howManyTimes(const std::string, char);
int howManyTimes(const char[], char);
int largest(const std::array<int, 5>&);
int largestIndex(const std::array<int, 5>&);
char occursMost(const std::string&);

int main() {
  std::cout << "Testing our howManyTimes()...." << std::endl;
  std::string message = "a New Nay";
  int result = howManyTimes(message, 'a');
  std::cout << "The character appears: " << result << " times!" << std::endl;

  char cArray[5]{'a', 'a', 'a', 'b', 'b'};
  int result2 = howManyTimes(cArray, 'a');
  std::cout << "The character appears (C-Style): " << result2 << " times!"
            << std::endl;

  std::array<int, 5> intArray = {1, 2, 3, 5, 9};
  int result3 = largest(intArray);
  std::cout << "The largest num in the array is: " << result3 << std::endl;

  int result4 = largestIndex(intArray);
  std::cout << "The largest num Index is: " << result4 << std::endl;

  std::string longStr = "Hello my old friendly fellow";
  char result5 = occursMost(longStr);
  std::cout << "Char that occurs the most is: " << result5 << std::endl;
}

char occursMost(const std::string& str) {
  std::unordered_map<char, int> characters;
  char frequentChar = '\0';
  int numOccurance = 0;

  // Build the map
  for (const char c : str) {
    characters[c]++;
  }

  for (const auto& c : characters) {
    if (c.second > numOccurance) {
      numOccurance = c.second;
      frequentChar = c.first;
    }
  }

  return frequentChar;
}

int largestIndex(const std::array<int, 5>& intArray) {
  int largest = intArray[0];
  int largestIndex = 0;

  for (int i = 1; i < intArray.size(); i++) {
    if (intArray[i] > largest) {
      largest = intArray[i];
      largestIndex = i;
    }
  }

  return largestIndex;
}

int largest(const std::array<int, 5>& intArray) {
  int largest = intArray[0];

  for (int num : intArray) {
    if (num > largest) {
      largest = num;
    }
  }

  return largest;
}

int howManyTimes(const std::string msg, char character) {
  int charCount = 0;

  for (char _char : msg) {
    if (_char == character) {
      charCount++;
    }
  }

  return charCount;
}

int howManyTimes(const char cStringArray[], char character) {
  int charCount = 0;

  for (int i = 0; i < cStringArray[i] != '\0'; i++) {
    if (cStringArray[i] == character) {
      charCount++;
    }
  }

  return charCount;
}
