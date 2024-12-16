// Write a function that gets passed a std::string, and a char, have it return
// the number of times that the char occurs in the string. Repeat this question
// but use a c-style string instead.

// Write a function that gets passed an array of integers and returns the
// largest int in the array.

// Write a function that gets passed an array of integers and returns the index
// of the largest int in the array.

// Write a function that gets passed a std::string, and returns the character
// that occurs the most times in the string. Repeat this with a c-string.

// Write a function that gets passed a std::string, have it modify the string to
// replace all vowels with the ‘*’ character. Print the string outside the
// function to verify it worked.

// Create a student struct that contains an int id, and a std::string name.
// - Write a function that gets passed an(int) id, and a (std::string) name,
// have it dynamically allocate a Student struct and return the address to the
// caller.
// - Ensure it can be passed a string literal for the name argument. The caller
// should then print out the name and id of the student.

// Write a function that takes in 2 c-style strings. Have the function
// concatenate the 2 strings and return a newly (heap) allocated c-style string
// to the caller.

#include <array>
#include <iostream>
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
