// Write a function that gets passed a std::string, and a char, have it return
// the number of times that the char occurs in the string. Repeat this question
// but use a c-style string instead.

#include <array>
#include <cstring>
#include <iostream>
#include <unordered_map>
int stringRepeatNum(std::string str, char c) {
  int sum = 0;
  for (auto &character : str) {
    if (character == c) {
      sum += 1;
    };
  }
  // for (int i = 0; i < str.size(); i++) {
  //   if (str[i] == c) {
  //     sum += 1;
  //   }
  // }

  return sum;
}

// Write a function that gets passed an array of integers and returns the
// largest int in the array.

int largestIntArray(std::array<int, 3> arr) {
  int largest = arr[0];

  for (auto &num : arr) {
    if (num > largest)
      largest = num;
  }

  return largest;
}

// Write a function that gets passed an array of integers and returns the index
// of the largest int in the array.

int largestIndexArray(std::array<int, 3> arr) {
  int largest = arr[0];
  int index = 0;

  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > largest) {
      largest = arr[i];
      index = i;
    }
  }

  return index;
}

// Write a function that gets passed a std::string, and returns the character
// that occurs the most times in the string. Repeat this with a c-string.

char characterSpamString(std::string str) {
  std::unordered_map<char, int> map;
  for (auto &s : str) {
    map[s]++;
  }

  int largest = 0;
  char spam;
  for (auto &item : map) {
    if (item.second > largest) {
      largest = item.second;
      spam = item.first;
    }
  }

  return spam;
}

char characterSpamCString(char str[]) {
  std::unordered_map<char, int> map;
  for (int i = 0; str[i] != '\0'; i++) {
    map[str[i]]++;
  }

  int largest = 0;
  char spam;
  for (auto &item : map) {
    if (item.second > largest) {
      largest = item.second;
      spam = item.first;
    }
  }

  return spam;
}

// Write a function that gets passed a std::string, have it modify the string to
// replace all vowels with the ‘*’ character. Print the string outside the
// function to verify it worked.

void changeString(std::string &str) {
  std::array<char, 12> vowels = {'a', 'e', 'i', 'o', 'u', 'A',
                                 'E', 'I', 'O', 'U', 'y', 'Y'};

  for (auto &s : str) {
    for (auto &v : vowels) {
      if (s == v)
        s = '*';
    }
  }
}

// Create a student struct that contains an int id, and a std::string name.
// - Write a function that gets passed an(int) id, and a (std::string) name,
// have it dynamically allocate a Student struct and return the address to the
// caller.
// - Ensure it can be passed a string literal for the name argument. The caller
// should then print out the name and id of the student.

struct Student {
  int id;
  std::string name;

  Student(int id, std::string name) : id{id}, name{name} {};
};

Student *newStudent(int id, std::string name) {
  Student *nStudent = new Student(id, name);
  return nStudent;
}

// Write a function that takes in 2 c-style strings. Have the function
// concatenate the 2 strings and return a newly (heap) allocated c-style string
// to the caller.

char *concatStrings(char *c1, char *c2) {
  const int len1 = strlen(c1);
  const int len2 = strlen(c2);
  const int len = len1 + len2 + 1;

  char *newStr = new char[len];
  strcpy(newStr, c1);
  strcat(newStr, c2);

  return newStr;
}

int main() {
  std::cout << "Testing stringRepeatNum()\n";
  std::string str = "Hello";
  char c = 'l';
  // std::cout << "[ " << c << " ] occurs: " << stringRepeatNum(str, c)
  // << " times!\n";
  std::cout << "\nTesting largestIntArray()\n";
  std::array<int, 3> arr = {1, 5, 4};
  // std::cout << "Largest Int in the array is: " << largestIntArray(arr) <<
  // "\n";
  std::cout << "\nTesting largestIndexArray()\n";
  // std::cout << "Largest Index in the array is: " << largestIndexArray(arr)
  // << "\n";
  std::cout << "\nTesting characterSpamString()\n";
  // std::cout << "[ " << characterSpamString(str)
  // << " ] has appeared the most!\n";
  std::cout << "\nTesting characterSpamCString()\n";
  char str1[] = "Heelo";
  // std::cout << "[ " << characterSpamCString(str1)
  // << " ] has appeared the most!\n";
  std::cout << "\nTesting changeString()\n";
  std::string str2 = "Money";
  std::cout << "Before: " << str2 << "\n";
  // changeString(str2);
  std::cout << "After: " << str2 << "\n";
  std::cout << "\nTesting newStudent()\n";
  std::string name = "Kiefer";
  int id{1};
  // Student *student = newStudent(id, "Kiefer");
  // std::cout << "Student name: " << student->name
  // << ", Student ID: " << student->id << "\n";
  // delete student;
  std::cout << "\nTesting concatStrings()\n";
  char str3[] = "Hay";
  // std::cout << "New String: " << concatStrings(str1, str3) << "\n";
}
