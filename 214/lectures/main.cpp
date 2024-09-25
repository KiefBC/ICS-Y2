#include <iostream>

// The intent of the code below is to
// - review pointer syntax (* and & operators) used to pass an argument
//   by address (allows the argument to be modified within a function).


// The function below should append (add) the string b to the first string a.
// The first string should be changed as a result.
// It currently doesn't work (because a and b are passed by value).
// Use what we learned in the last class (pass by address using pointers) to fix it!
// See main() for a sample call to the function (and expected output).
// Hint: Both the function and the call in main() will require modification. 
void append(std::string* a, std::string* b) {
    *a += *b;
}

// The function below should set the GPA of the student passed in so that the 
// original argument (a student record) is affected.
// See main() for a sample call to the function (and expected output).
// Modify it (and the function call in main() ) to fix the problem.
struct Student {
    std::string name{ "unknown" };
    float gpa{ };
};

void setGpa(Student* s, float newGpa) {
    s->gpa = newGpa;
    (*s).gpa = newGpa;
}


int main() {
    // Sample call for Question 1
    std::string name1{ "Dennis" };
    std::string name2{ "Ritchie" };
    append(&name1, &name2);				// requires modification to work
    std::cout << name1 << '\n';			// expected output: "DennisRitchie"

    // Sample call for Questions 2
    Student s1{ "Bjarne", 3.0 };
    setGpa(&s1, 3.3);					// requires modification to work
    std::cout << s1.gpa << '\n';		// expected output: 3.3
}