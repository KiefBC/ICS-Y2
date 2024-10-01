
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <unordered_map>
#include <cstring>

int numOfTimesRepeat(const std::string&, char);
int numOfTimesRepeat(const char[], char);
int largestInArray(const int[], int);
int indexOfLargest(const int[], int);
char repeatCharacter(std::string);
void vowelReplacer(std::string&);
char* stringConcat(const char*, const char*);

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
    std::string name;
    int id{};
};

Student1* createStudent(const std::string&, int);

#endif