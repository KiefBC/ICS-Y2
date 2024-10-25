#include <iostream>
#include <vector>
#include <array>
#include <cstring>

// The sample questions below are to give you some practice at working through
// practical questions in preparation for the midterm. Often questions will
// include the code in a "use example" that will allow you to test it.
//  
// Note: In an exam situation partial marks are deducted if parameters 
// aren't passed by best practice (given a specific scenario).
// eg: 
// void print(std::string msg) {
//    std::cout << msg << '\n';
// }
//  -0.5 points for pass by value instead of reference (it's an object!)
//  -0.5 points because it should also be been const (no changes to msg 
//       inside the function)
// 

// Topics: 
// - pass by value vs pass by ref 
// ============================================================
// Question [3 pts]
// Write a function called swapByRef()
// - param 1: a char
// - param 2: a char
//   return: nothing. [1pt] The original argument should be modified
// 
//   Swap the first and second parameter
// Use example:
//	char c1{ 'a' };
//	char c2{ 'b' };
//	swapByRef(c1, c2);
//	std::cout << c1 << c2 << '\n';  // output: ba
// 
// [1 pt] explain in a comment why swap("a", "b") won't work.
// Use example: 
//    see testQ1() below
// -------------------------------------------------------------
void swapByRef(char& charOne, char& charTwo) {
    char temp = charOne;
    charOne = charTwo;
    charTwo = temp;
}


void testQ1() {
	std::cout << "testQ1()----------\n";
	char c1{ 'a' };
	char c2{ 'b' };
	 swapByRef(c1, c2);
	std::cout << c1 << c2 << '\n';  // output: ba
}



// Topics: 
// - pass by address
// - dereferencing pointers
// ============================================================
// Question [5 pts]
// [2] Write a function called swapByAddress()
// - param 1: a pointer to a char
// - param 2: a pointer to a char
//   return: nothing. [1pt] The original arguments should be modified
// [2 pt] Make changes to the use example below to show what would need to 
//        change to make this work.
// 
// Use example:
//   see testQ2() below
// -------------------------------------------------------------
void swapByAddress(char* charOne, char* charTwo) {
    const char cTemp = *charOne;
    *charOne = *charTwo;
    *charTwo = cTemp;
}

void testQ2() {	
	std::cout << "testQ2()----------\n";
	char c1{'a'};
	char c2{'b'};
	swapByAddress(&c1, &c2);
	std::cout << c1 << c2 << '\n';  // output: ba
}

// Topics:
// - basic parameter passing (value, ref, const ref, address)
// =============================================================
// Question [1 pt]
// The logMessage() function below works, however it is inefficient.
//   Change it to make it more efficient, and still have it work with
//   the call made in testLogMessage()
// Use example:
//   see testQ3() below
// -------------------------------------------------------------
void logMessage(const std::string& msg) {
	std::cout << msg << '\n';
}

void testQ3() {
	std::cout << "testQ3()----------\n";
	logMessage("testing 123");
}


// Topics: 
// - char/ASCII manipulation
// - basic parameter passing (value, ref, const ref, address)
// ============================================================
// Question [3 pts]
// Write a function called capitalize() 
// - param 1: a std::string to modify 
// - return: nothing. [1 pt] The original argument should be modified.

// - [1 pt] show you know how to convert lowercase letters in a std::string to 
//          uppercase by using math on ascii values (don't use toUpper()).
//       'a' is ASCII 97
//       'A' is ASCII 65
// 
// Use example:
//   see testQ4() below
// -------------------------------------------------------------
void capitalize(std::string& msg) {
    for (auto& letter : msg) {
        if (letter > 'Z') {
            letter -= 32;
        }
    }
}


void testQ4() {
	std::cout << "testQ4()----------\n";
	std::string location = "Victoria, British Columbia";
	capitalize(location);
	std::cout << location << '\n';	//  output: VICTORIA, BRITISH COLUMBIA
}

// Topics: 
// - structs
// - basic parameter passing (value, ref, const ref, address)
// =============================================================
// Question [3 pts]
// - Write a function called getArrayStats(). 
// [1 pt]:
// - param 1: a std::array of 6 integers
// 
// [2 pt]:
// - return: ArrayStats: a struct containing: 2 integers
//     minIndex  // the index of the min value found in the array
//     maxIndex  // the index of the max value found in the array			  
//			 	 // both should be -1 if the array is empty.
//  
// Use example:
//   see testQ5() below
// -------------------------------------------------------------
struct ArrayStats {
    int min;
    int max;
};

ArrayStats getArrayStats(std::array<int, 6>& array) {
    int min = 0;
    int max = 0;

    for (int i = 0; i < array.size(); i++) {
        if (array[min] > array[i]) {
            min = i;
        }

        if (array[max] < array[i]) {
            max = i;
        }
    }

    ArrayStats newArray{};
    newArray.min = min;
    newArray.max = max;

    return newArray;
}

void testQ5() {
	std::cout << "testQ5()----------\n";
	std::array<int, 6> intArr{ 33, 55, 11, 22, 99, 11 };
	ArrayStats stats = getArrayStats(intArr);
	std::cout << "min:" << stats.min << ", max:" << stats.max <<'\n';  // output: min: 2, max: 4
}

// Topics:
// - C-style strings
// - basic parameter passing (value, ref, const ref, address)
// =============================================================
// Question [3.5 pts]
// [2 pt]:
// - Write a function called censorCString() 
//   Given a C-style string and a collection of "censored" characters, replace
//   occurences of censored characters (in the original C-style string) with a '*'
// [1.5 pt]:
// - param 1: a c-string (NOT a std::string) to be modified 
// - param 2: a std::vector of censored chars.
// - return: none
// 
// Use example:   
//   see testQ6() below
// -------------------------------------------------------------
void censorString(char* msg1, std::vector<char>& msg2) {
    for (int i = 0; msg1[i] != '\0'; i++) {
        for (auto& letter : msg2) {
            if (msg1[i] == letter) {
                msg1[i] = '*';
            }
        }
    }
}

void testQ6() {
	std::cout << "testQ6()----------\n";

	std::vector<char> blockedChars{ 'M', 'i' };
	char location[]{ "Mississippi" };
	censorString(location, blockedChars);
	std::cout << location << '\n';		//	output: **ss*ss*pp*
}

// Topics:
// - structs
// - std::vector
// - random number generation
// - basic parameter passing (value, ref, const ref, address)
// - return by address
// =============================================================
// Question [7 pts]
// - [1] Define a Point struct containing 2 ints: x and y
// 
// - [2 pt] Write a function: createRandomPoints().
// -   param 1: int the number of Points to create
// -   param 2: int, the max random int value x or y can be [0..max]
// - return: a std::vector of Points
// 
//	   Create a std::vector of Point structs.
//        hint: use v.push_back( x ) to add an item to a vector v.
//		  Initialize each Point x and y to a random int in the range [0...param2]
//		  (inclusive - ie: [0...2] includes 0, 1, and 2) 
//
// - [1 pt] Write a function printPoints().
// - param 1: an std::vector of Point structs-  
// - output:  Point[x,y]
//			  Point[x,y]
//			  ...
//			  Point[x,y]
// - [1 pt] use a ranged for loop and make it as efficient as possible (use a reference)
//
// In the testQ7() function below:
// - [1 pt] Call createRandomPoints() and store the result in local variable.
// - [1 pt] call printPoints to print the std::vector created earlier
// -------------------------------------------------------------
struct Points {
    int x;
    int y;
};

std::vector<Points> createRandomPoints(int points, int max) {
    std::vector<Points> vPoints;

    for (int i = 0; i < points; i++) {
        Points p;
        p.x = rand() % max;
        p.y = rand() % max;

        vPoints.push_back(p);
    }

    return vPoints;
}

void printPoints(std::vector<Points>& vP) {
    for (auto& points : vP) {
        std::cout << "Point[" << points.x << ", " << points.y << "]\n";
    }
}

void testQ7() {
	std::cout << "testQ7()----------\n";
    int numPoints{5};
    int maxRange{5};

    std::vector<Points> points = createRandomPoints(numPoints, maxRange);
    printPoints(points);
}


// Topics:
// - pass by address
// - return by address
// - dynamic memory allocation
// - C-style strings
// =============================================================
// Question [4 pts]
// - Uncomment and complete the function that has beens started: concatCStrings()
// -   param 1: a C-style string
// -   param 2: a C-style string
// -   return: the address of the resulting C-Style string
// 
// - Dynamically allocate memory for a C-style string
// - Fill it with contents of the two C-style strings passed in
// - Ensure the new string can be printed properly (without errors or extra chars)
//
//   The shell of the function is given below to get you started
// use example:
//   see test Q8 below 
// -------------------------------------------------------------
char* concatCStrings(const char msg1[], const char msg2[]) {
	const size_t len1 = strlen(msg1);
	const size_t len2 = strlen(msg1);
    const size_t length = len1 + len2 + 1;

    char* newString = new char[length];

    strcpy(newString, msg1);
    strcat(newString, msg2);

	return newString;  // replace this return value as part of this question
}

void testQ8() {	
	std::cout << "testQ8()----------\n";

	char* pResult{ nullptr };
	pResult = concatCStrings("hi", "fi");	// uncomment this when ready to test
	if (pResult) {
		std::cout << pResult << "\n";	// expected output: "hifi"
		delete[] pResult;
		pResult = nullptr;
	}
}

// Topics:
// - reading input
// - std::vector
// - basic parameter passing (value, ref, const ref, address)
// =============================================================
// Question [6 pts]
// *** For this question, assume input is valid (don't handle invalid input).
// 
// STEP 1: Write a function getGradesFromUser() that returns a vector of doubles. 
//         It should:
// - [1 pt] Prompt the user with "Enter a grade (-1 to finish):" - read the 
//          grade in as a double
// - [1 pt] Add the grade to a vector (& continue these 2 steps until the user
//          enters -1)
//          Tip: To add a grade to a vector v, use v.push_back(grade) 
// - params: none
// [0.5 pt]:
// - return: a std::vector of doubles.
//
// STEP 2: Write a function getAvgGrade()
//   Calculate and return an average grade from a vector of grades:
// [1 pt]:
// - param 1: a std::vector of grades.
// [1.5 pt]:
// - return: a double, the average of all grades in the vector
//           (if the vector is empty the average should be 0)
//  
// In testQ10() below:
// - [1 pt] Call the 2 functions above to prompt the user for grades, 
//          and print the average to the console. 
// -------------------------------------------------------------
std::vector<double> getGradesFromUser() {
    double userGrade;
    std::vector<double> grades;

    do {
        std::cout << "Enter a Grade (-1 to quit): ";
        std::cin >> userGrade;

        if (userGrade != -1) {
            grades.push_back(userGrade);
        }

    } while (userGrade != -1);

    return grades;
}

double getAvgGrade(std::vector<double>& grades) {
    double sum = 0;

    for (auto& grade : grades) {
        sum += grade;
    }

    return sum / static_cast<double>(grades.size());
}

void testQ9() {
	std::cout << "testQ9()----------\n";
    std::vector<double> userGrades = getGradesFromUser();
    double avg = getAvgGrade(userGrades);
    std::cout << avg << "\n";
}

// Topics:
// - return by reference
// - basic parameter passing (value, ref, const ref, address)
// =============================================================
// Question [2 pt]
// The getLongerString() function (below) currently determines the longer string
//   and returns by value.  If a change is made to the value returned (in the caller),
//   it doesn't (currently) affect the original.
//  
// Modify getLongerString() input parameters and return type so that a change 
// to the result (in the caller) will affect the original argument.
// Hint: Changes are required in both functions (getLongerString() and testQ12())
// to make this work.
// use example:
//   see testQ10()
// -------------------------------------------------------------
std::string& getLongerString(std::string& s1, std::string& s2) {
	if (s1.length() > s2.length()) {
		return s1;
	}
	return s2;
}

void testQ10() {
	std::cout << "testQ10()----------\n";
	std::string str1{ "123" };
	std::string str2{ "12345" };
	std::string longerString{ getLongerString(str1, str2) };
	longerString += "!";
	std::cout << str2 << "\n";		// should output: 12345!
}


// Topics:
// - pointers
// - linked lists
// - pass by address
// - return by address
// =============================================================
// Question [4 pt]
//	Given an employee struct, and the linked list setup in testEmployee()
//  Write a function findEmployeeById()
//  It should iterate through the list looking for a node with a specific id.
//  - param 1: a pointer to the front of the list
//  - param 2: an int : the id of the node we are searching for
//  - returns: the address of the node we're searching for (or nullptr if 
//       not found)
// -------------------------------------------------------------
struct Employee {
	int id;
	Employee* pNext;
};

Employee* findEmployeeById(Employee* pHead, int id) {
    Employee* current = pHead;

    while (pHead != nullptr) {
        if (current->id == id) {
            return current;
        }

        current = current->pNext;
    }

    return nullptr;
}


void testQ11() {
	std::cout << "testQ11()----------\n";

	// create a linked list with 2 nodes in it (pEmployees points to the first node)
	// eg:  pEmployees->[id:2]->[id:1]->//
	Employee* pEmp2 = new Employee{ 1, nullptr };
	Employee* pEmployees = new Employee{ 2, pEmp2 };
	// search the list for id:2
	int searchId{ 2 };

	Employee* pFound = nullptr;
	// uncomment these lines when ready to test:
	pFound = findEmployeeById(pEmployees, searchId);
	if (pFound) {
		std::cout << "found id: " << pFound->id << '\n';
	}
	else {
		std::cout << "id: " << searchId << " not found\n";
	}

    delete(pEmp2);
    delete(pEmployees);
}




int main() {
	//use this space for testing and for output from the questions above
	testQ1();
	testQ2();
	testQ3();
	testQ4();
	testQ5();
	testQ6();
	testQ7();
	testQ8();
	testQ9();
	testQ10();
	testQ11();		
}