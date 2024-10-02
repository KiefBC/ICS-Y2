#include "main.h"

int main() {
    std::string input = "Hello";
    constexpr char letter = 'l';
    constexpr char charString[] = "Hello My Soon";
    const int madeArray[5] = { 1, 8, 2, 2, 5 };
    constexpr int size = std::size(madeArray);
    const std::string studentName = "John";
    const std::string studentName2 = "Mick";
    constexpr int id = 1;
    constexpr int id2 = 2;

    std::cout << "Number of times " << letter << " repeats in a std::string: ";
    std::cout << numOfTimesRepeat(input, letter) << std::endl;;
    std::cout << "The number of times " << letter << " repeats in a C-String: ";
    std::cout << numOfTimesRepeat(charString, letter) << std::endl;

    std::cout << "\nThe largest number the array is: ";
    std::cout << largestInArray(madeArray, size) << std::endl;
    std::cout << "The index of the largest number in the array is: ";
    std::cout << indexOfLargest(madeArray, size) << std::endl;

    std::cout << "\nThe repeating characters in the array is: ";
    std::cout << repeatCharacter(input) << std::endl;
    std::cout << "The repeating character in the C Array is: ";
    std::cout << repeatCharacter(charString) << std::endl;

    std::cout << "\nOriginal String: " << input << std::endl;
    vowelReplacer(input);
    std::cout << "Modified String: " << input << std::endl;

    const Student1* student1 = createStudent(studentName, id);
    std::cout << "Student1 Struct w/o Constructor Name: " << student1->name << std::endl;
    std::cout << "Student1 Struct w/o Constructor Student1 ID: " << student1->id << std::endl;

    const Student1* student2 = createStudent(studentName2, id2);
    std::cout << "Student2 w/o Constructor Name: " << student2->name << std::endl;
    std::cout << "Student2 w/o Constructor ID: " << student2->id << std::endl;

    delete student1;
    delete student2;

    Student student3("Alice", 101);
    Student student4("Jake", 102);

    const char* jake = "Jake";
    const char* alice = "Alice";
    char* concatStrings = stringConcat(jake, alice);
    std::cout << concatStrings << std::endl;
    free(concatStrings);

    return 0;
}

char* stringConcat(const char* jake, const char* alice) {
    std::cout << "\nConcating Strings...." << std::endl;
    const size_t length1 = std::strlen(jake);
    const size_t length2 = std::strlen(alice);

    const auto result = new char[length1 + length2 + 1];
    strcpy(result, jake);
    strcat(result, alice);

    return result;
}

Student1* createStudent(const std::string& name, const int id) {
    std::cout << "\nCreating new Student..." << std::endl;
    Student1* newStudent = new Student1;

    newStudent->name = name;
    newStudent->id = id;

    return newStudent;
}

void vowelReplacer(std::string& input) {
    const char VOWELS[] = "aeiou";
    const char replacement = '*';

    for (char& c : input) {
        char lowerCase = std::tolower(c);
        if (std::strchr(VOWELS, lowerCase)) {
            c = replacement;;
        }
    }
}

char repeatCharacter(const char* string) {
    std::unordered_map<char, int> charMap;
    char mostFrequentChar = '\0';
    int maxCount = 0;

    for (int i = 0; string[i] != '\0'; i++) {
        charMap[string[i]]++;

        if (charMap[string[i]] > maxCount) {
            maxCount = charMap[string[i]];
            mostFrequentChar = string[i];
        }
    }

    return mostFrequentChar;
}

char repeatCharacter(const std::string& input) {
    std::unordered_map<char, int> charMap;
    char mostFrequentChar = '\0';
    int maxCount{ 0 };

    for (char c : input) {
        charMap[c]++;

        if (charMap[c] > maxCount) {
            maxCount = charMap[c];
            mostFrequentChar = c;
        }
    }

    return mostFrequentChar;
}

int largestInArray(const int array[], int size) {
    int max = array[0];

    for (int i = 0; i < size; i++) {
        if (max < array[i]) {
            max = array[i];
        }
    }

    return max;
}

int indexOfLargest(const int array[], int size) {
    int max = array[0];
    int indexOfLargest = array[0];

    for (int i = 0; i < size; i++) {
        if (max < array[i]) {
            max = array[i];
            indexOfLargest = i;
        }
    }

    return indexOfLargest;
}

int numOfTimesRepeat(const std::string& readString, char letterRepeated) {
    int numOfRepeats{ 0 };

    for (char c : readString) {
        if (c == letterRepeated) {
            numOfRepeats++;
        }
    }

    return numOfRepeats;
}

int numOfTimesRepeat(const char charString[], char letterRepeated) {
    int numOfRepeats{ 0 };

    for (int i = 0; charString[i] != '\0'; i++) {
        if (charString[i] == letterRepeated) {
            numOfRepeats++;
        }
    }

    return numOfRepeats;
}
