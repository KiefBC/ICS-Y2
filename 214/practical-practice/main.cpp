#include "main.h"

int numOfTimes(const std::string& name, char repeatChar) {
	int repeatCount = 0;

	for (char currChar : name) {
		if (currChar == repeatChar) {
			repeatCount++;
		}
	}

	return repeatCount;
}

int numOfTimes(char cString[], char repeatChar) {
	int repeatCount = 0;

	for (int i = 0; cString[i] != '\0'; i++) {
		if (cString[i] == repeatChar) {
			repeatCount++;
		}
	}

	return repeatCount;
}

int largestNum(const int numArray[], const int size) {
	int largest = numArray[0];

	for (int i = 0; i < size; i++) {
		if (numArray[i] > largest) {
			largest = numArray[i];
		}
	}

	return largest;
}

int indexLargest(const int numArray[], const int size) {
	int largest = numArray[0];
	int index = 0;

	for (int i = 0; i < size; i++) {
		if (numArray[i] > largest) {
			largest = numArray[i];
			index = i;
		}
	}

	return index;
}

char returnRepeatChar(const std::string& string) {
	char repeatChar = '\0';
	int maxCount = 0;
	std::unordered_map<char, int> map;

	for (const auto& currChar : string) {
		map[currChar]++;
	}

	for (const auto& curr : map) {
		if (curr.second > maxCount) {
			maxCount = curr.second;
			repeatChar = curr.first;
		}
	}

	return repeatChar;
}

char returnRepeatChar(const char cString[]) {
	char repeatChar = '\0';
	int maxCount = 0;
	std::unordered_map<char, int> map;

	for (int i = 0; cString[i] != '\0'; i++) {
		map[cString[i]]++;
	}

	for (const auto& currChar : map) {
		if (currChar.second > maxCount) {
			maxCount = currChar.second;
			repeatChar = currChar.first;
		}
	}

	return repeatChar;
}

void vowelReplacer(std::string& string) {
	for (auto& currChar : string) {
		for (auto& vowel : Constants::VOWELS) {
			if (currChar == vowel) {
				currChar = '*';
			}
		}
	}
}

Student* createStudent(int id, std::string& name) {
	Student* student = new Student;
	student->id = id;
	student->name = name;

	return student;
}

char* stringConcat(char cString[], char cString2[]) {
	size_t length1 = strlen(cString);
	size_t length2 = strlen(cString2);
	size_t length = length1 + length2 + 1; // + 1 for the null terminator

	char* pString = new char[length];

	// strcpy_s(pString, length, cString);
	// strcat_s(pString, length, cString2);

	return pString;
}

int main() {
	int repeatResult = numOfTimes(Constants::NAME, Constants::CHARACTER);
	std::cout << "Repeat Char (std::string) " << Constants::CHARACTER << " repeated " << repeatResult << " times" << std::endl;

	char cString[] = { "Kiefer Kyler Killer" };
	int repeatResult2 = numOfTimes(Constants::CSTRING, Constants::CHARACTER);
	std::cout << "Repeat Char (c string) " << Constants::CHARACTER << " repeated " << repeatResult2 << " times" << std::endl;

	
	int largestNumResult = largestNum(Constants::ARRAYNUM, Constants::SIZE);
	int indexResult = indexLargest(Constants::ARRAYNUM, Constants::SIZE);
	std::cout << "Largest num is " << largestNumResult << std::endl;
	std::cout << "Index of Largest num is " << indexResult << std::endl;

	char resultChar = returnRepeatChar(Constants::NAME);
	char resultChar2 = returnRepeatChar(Constants::CSTRING);
	std::cout << "Repeated Character is " << resultChar << std::endl;
	std::cout << "Repeated Character is (c string) " << resultChar2 << std::endl;

	std::string beforeVowels{ "Kiefer Kyler Killer" };
	std::cout << "Before Vowel Replacement: " << beforeVowels << std::endl;
	vowelReplacer(beforeVowels);
	std::cout << "After Vowel Replacement: " << beforeVowels << std::endl;

	std::string studentName { "Kiefer Kyler Killer" };
	Student* student = createStudent(1, studentName);
	std::cout << "Student: " << student->name << " has the ID: " << student->id << std::endl;
	delete student;

	char* newString = stringConcat(Constants::CSTRING, Constants::CSTRING);
	std::cout << "Concatted String: " << newString << std::endl;
	delete newString;

	return 0;
}