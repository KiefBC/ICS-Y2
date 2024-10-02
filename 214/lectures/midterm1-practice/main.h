//
// Created by kiefh on 2024-10-01.
//

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <unordered_map>
#include <cstring>

int numOfTimesRepeat(const std::string&, char);
int numOfTimesRepeat(const char[], char);
int largestInArray(const int[], int);
int indexOfLargest(const int[], int);
char repeatCharacter(const std::string&);
char repeatCharacter(const char*);
void vowelReplacer(std::string&);
char* stringConcat(const char*, const char*);

// This works, but don't do it this way
struct Student {
    std::string name;
    int id{};

    Student(const std::string& studentName, const int studentId) {
        std::cout << "\nCreating a better Student..." << std::endl;

        this->name = studentName;
        this->id = studentId;

        this->displayStatus();
    }

    void displayStatus() const {
        std::cout << "Student Struct /w Constructor..." << std::endl;
        std::cout << "Name: " << this->name << ", ID: " << this->id << std::endl;
    }
};

struct Student1 {
    std::string name {"unknown"};
    int id{0};
};

Student1* createStudent(const std::string&, int);

#endif //MAIN_H

