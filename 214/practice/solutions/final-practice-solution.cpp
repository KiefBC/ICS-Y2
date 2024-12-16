// ICS 214 Fall 2024 review
// The tasks below attempt to cover as many topics as possible from Module 10
// through 22.

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

// ------------------------------
// TASK 1 - topics: classes, heap allocation/deallocation, pointers, operator
// overloading
// ------------------------------
// Write a LinkedList class that is capable of storing chars
// For simplicity, write it inline (you don't need to break the functions out of
// the class definition) Use the following starting point:
// struct Node {
//    char value;
//    Node* pNext;
//};
//
// class LinkedList {
// private:
//    Node* pHead;            // points to the first element
//    Node* pTail;            // points to the last element
// public:
//    void add(char);         // add an element at the end (tail)
//    bool contains(char);    // return true if element is in the list
//    void empty();           // empty (deallocate) the list
//    ~LinkedList();          // destructor
//};

// Overload the insertion operator (operator<<()) to output a list
// (containing 'A', and 'B') in this format:  [A B ]

struct Node {
  char value;  // The Value of the Node
  Node *pNext; // The next Node in the Linked List
};

class LinkedList {
private:
  Node *pHead; // The Head/First node in the Linked List
  Node *pTail; // The last Node in the Linked List
public:
  LinkedList() : pHead(nullptr), pTail(nullptr) {};

  // Adds an element to a Linked List
  void add(char value) {
    Node *newNode = new Node();
    newNode->value = value;
    newNode->pNext = nullptr;

    if (pHead == nullptr) {
      pHead = newNode;
      pTail = newNode;
    } else {
      pTail->pNext = newNode;
      pTail = newNode;
    }
  }

  // Checks if a LinkedList contains a given value
  bool contains(char value) {
    Node *pCurrent = pHead;
    while (pCurrent != nullptr) {
      if (pCurrent->value == value) {
        return true;
      }
      pCurrent = pCurrent->pNext;
    }
    return false;
  }

  // Empties the Linked List
  void empty() {
    Node *pCurrent = pHead;
    while (pCurrent != nullptr) {
      Node *next = pCurrent->pNext;
      delete pCurrent;
      pCurrent = next;
    }
    pTail = nullptr;
    pHead = nullptr;
  }

  ~LinkedList() { empty(); }

  friend std::ostream &operator<<(std::ostream &os, const LinkedList &list) {
    os << "[ ";
    Node *pCurrent = list.pHead;
    while (pCurrent != nullptr) {
      os << pCurrent->value << " ";
      pCurrent = pCurrent->pNext;
    }
    os << " ]";
    return os;
  }
};

void testLinkedList() {
  std::cout << "testLinkedList()-------------------------------\n";
  LinkedList list;
  list.add('A');
  list.add('B');
  list.add('C');
  std::cout << "contains B?: " << list.contains('B') << "\n";
  std::cout << "contains Z?: " << list.contains('Z') << "\n";
  std::cout << list << "\n"; // should ouput: [A B C ]
  list.empty();
  std::cout << list << "\n"; // should ouput: [ ]
}

// ------------------------------
// TASK 2 - topics: inheritance, method overriding, virtual functions
// ------------------------------
// Write a Set class that inherits from the LinkedList.
// Overload add() so that it only adds a char if it doesn't already exist.
// Test to ensure it works.

class Set : public LinkedList {
public:
  void add(char value) {
    if (!contains(value)) {
      LinkedList::add(value);
    };
  }
};

void testSet() {
  std::cout << "\ntestSet()--------------------------------------\n";
  Set set;
  set.add('A');
  set.add('B');
  set.add('B');
  std::cout << set << "\n"; // should output [A B ]
}

// ------------------------------
// TASK 3 - topics: OOP, operator overloading, throwing/catching exceptions,
//          template classes (both type & non-type params)
// ------------------------------
// Implement a MyArray class - capable of storing 3 doubles (using a c-style
// array) Use the following as a starting point:
// class MyArray {
// private:
//	static const int SIZE = 3;
//	double arr[SIZE];
//}
//
// At each step, test (using the debugger, breakpoints, and observing memory)
// that your method worked.
// 1) Initialize the array to 0's
// 2) Overload
// operator<< to allows a client to view the array. Example output: [0 0 0 ]
// 3)Overload operator[] to allow clients to get/set an element directly.
//   Assert that the index requested is valid.
//   eg: MyArray arr;  arr[0] = 1.5;
// 4) Overload operator[] to work with const MyArray instances (as a getter).
// 4) Write an at() method to do the same thing as operator[], however
//    if the index is invalid, throw a std::out_of_range exception with a
//    "invalid index" message. Verify the exception can be caught and printed in
//    main()
// 5) Template MyArray to handle any type. (eg: MyArray<char>)
// 6) Template MyArray to handle any size. (eg: MyArray<char, 5>)

template <typename T, int N = 3> class MyArray {
private:
  static const int SIZE = N; // The size of the array
  T arr[SIZE];               // The array that holds the values

public:
  MyArray() : arr{} {};
  friend std::ostream &operator<<(std::ostream &os, MyArray &array) {
    os << "[ ";
    for (auto &item : array.arr) {
      os << item << " ";
    }
    os << "]";
    return os;
  }

  // Allows us to set a value in the MyArray class
  T &operator[](int index) {
    assert(index < SIZE);
    return arr[index];
  }

  // Allows us to get a value from the MyArray class
  T operator[](int index) const {
    assert(index < SIZE);
    return arr[index];
  }

  // Allows us to see if a given value is in the MyArray class or modify the
  // index
  T &at(int index) {
    if (index >= SIZE) {
      throw std::out_of_range("Index out of Range");
    }
    return arr[index];
  }

  // Allows us to only see if a value is at a given index
  T at(int index) const {
    if (index >= SIZE) {
      throw std::out_of_range("Index out of Range");
    }
    return arr[index];
  }
};

void testMyArray() {
  std::cout << "\ntestMyArray()----------------------------------\n";
  MyArray<double, 5> arr;
  arr[0] = 1.5;
  std::cout << arr[0] << "\n";
  std::cout << arr[2] << "\n";
  arr.at(2) = 2.5;
  std::cout << arr.at(2) << "\n";
  std::cout << arr << "\n";
  MyArray<int, 5> arr1;
  arr1[0] = 1;
  std::cout << arr1[0] << "\n";
  std::cout << arr1[2] << "\n";
  arr1.at(2) = 2;
  std::cout << arr1.at(2) << "\n";
  std::cout << arr1 << "\n";
  MyArray<int> arr2;
  arr2[0] = 1;
  std::cout << arr2[0] << "\n";
  std::cout << arr2[2] << "\n";
  arr2.at(2) = 2;
  std::cout << arr2.at(2) << "\n";
  std::cout << arr2 << "\n";
}

// ------------------------------
// TASK 4 - topics: iterators, container classes, algorithms, template functions
// ------------------------------
//  1) Implement the function below:
template <typename Container> auto sum(const Container &arr) {
  int sum = 0;
  // for (auto& val : arr) {
  //   sum += val;
  // }
  auto begin = arr.begin();
  auto end = arr.end();
  while (begin != end) {
    sum += *begin; // Dereference the iterator to get the value
    begin++;
  }
  return sum;
}
//  2) verify it works by calling testSum() in main()
void testSum() {
  std::cout << "\ntestSum()--------------------------------------\n";

  std::array<int, 3> arr{2, 3, 4};
  std::cout << sum(arr) << "\n";
  std::vector<int> arr1{2, 3, 4};
  std::set<int> arr2{2, 3, 4};

  auto result = std::max_element(arr1.begin(), arr1.end());
  auto element = std::find(arr2.begin(), arr2.end(), 3);
  std::cout << "Max Element: " << *result << "\n";
  if (element != arr2.end()) {
    std::cout << "Element Found"
              << "\n";
  } else {
    std::cout << "Element not found";
  }
}
// 3) Rewrite the loop to use iterators (instead of for, or for-each)
// 4) Template this function to make it work with any container class.
//    Test it with a std::vector<int>, and a std::set<int>
// 5) Find and print the maximum value in the container class you used to test
// sum() by
//    using the std::max_element() algorithm. (#include <algorithm>)
// 6) Determine if a given value exists in the container class using the
// std::find() algorithm.

// ------------------------------
// TASK 5 - pointers, dynamic mem allocation/deallocation, copy constructor,
//          assignment operator, destructor, rule of 3, typecast
// ------------------------------
// Write a class MyInt that encapsulates storing an int on the heap.
//    Use the code below as a starting point.
class MyInt {
private:
  int *pInt;

public:
  MyInt(int value = 0) { pInt = new int{value}; }

  MyInt(const MyInt &other) { pInt = new int{other.getInt()}; }

  MyInt &operator=(const MyInt &other) {
    if (this == &other) {
      return *this;
    }
    deleteInt();
    pInt = new int{other.getInt()};
    return *this;
  }

  operator int() const { return getInt(); }

  int getInt() const {
    if (pInt == nullptr) {
      return 0;
    }
    return *pInt;
  }

  ~MyInt() { deleteInt(); }

  void deleteInt() {
    delete pInt;
    pInt = nullptr;
  }
};
// The class uses dynamically allocated memory from the heap.
// This means a shallow (or memberwise) copy is not sufficient when copies are
// made. Call the function below from main()
//    Uncomment each line (1 at a time)
//    Implement the required functionality in MyInt (test it works after each
//    step).

void testMyInt() {
  std::cout << "\ntestMyInt()------------------------------------\n";
  MyInt mi1;
  // dynamically allocate mem (value:0)
  std::cout << mi1.getInt() << "\n";
  // deallocate mem with destructor
  mi1.deleteInt();
  std::cout << mi1.getInt() << "\n";
  // verify it worked MyInt mi2(5);
  MyInt mi2{5};
  std::cout << mi2.getInt() << "\n";
  mi2.deleteInt();
  std::cout << mi2.getInt() << "\n";
  mi2 = {10};
  // dynamically allocate mem (value: param1) verify it worked
  const MyInt mi3 = mi2;
  std::cout << mi3.getInt() << "\n";
  int x = mi3;
  // provide a typecast to make this conversion implicit.
  std::cout << x << "\n";
}

// ------------------------------
// TASK 6 - OOP, inheritance, polymorphism, base class var initialization,
// virtual functions,
//			pure virtual functions, abstract classes, downcasting
//(dynamic_cast), 			virtual destructors
// ------------------------------

class Student {
protected:
  const int id;

public:
  Student(int id) : id(id) { std::cout << "Student Constructor Called\n"; }

  // Returns the ID of the student
  int getId() const { return id; }

  // Returns the type of the student
  virtual std::string getType() const = 0;

  virtual ~Student() { std::cout << "Student Destructor Called\n"; }
};

class UndergradStudent : public Student {
public:
  UndergradStudent(int id) : Student(id) {
    std::cout << "UndergradStudent Constructor Called\n";
  }

  std::string getType() const override { return "UndergradStudent"; };
};

class GradStudent : public Student {
private:
  std::string degree;

public:
  GradStudent(int id, std::string degree) : Student(id), degree(degree) {
    std::cout << "GradStudent Constructor Called\n";
  }

  std::string getType() const override { return "GradStudent"; }

  std::string getDegree() const { return degree; }
};

class RegistrationList {
private:
  std::vector<Student *> students;

public:
  RegistrationList() { std::cout << "RegistrationList Constructor Called\n"; }

  // Adds a student to the list
  void add(Student *student) { students.push_back(student); }

  // Prints each student in the list and their ID, Type and Degree
  void print() {
    for (auto student : students) {
      std::cout << "ID: " << student->getId()
                << " Type: " << student->getType();
      if (dynamic_cast<GradStudent *>(student)) {
        std::cout << " Degree: "
                  << dynamic_cast<GradStudent *>(student)->getDegree();
      }
      std::cout << "\n";
    }
  }

  ~RegistrationList() {
    for (auto student : students) {
      delete student;
    }
    std::cout << "RegistrationList Destructor Called\n";
  }
};

// This one covers a lot of ground. Refer to the Student_UML diagram specified
// in the Review Module. Once the classes in the UML diagram are set up, call
// testStudents() in main().
void testStudents() {
  std::cout << "\ntestStudents()---------------------------------\n";
  int idGenerator{0};
  // This will print that the RegistrationList Constructor was called
  RegistrationList regList;
  // This will print that the Student Constructor was called
  // Then the UndergradStudent Constructor was called
  regList.add(new UndergradStudent(idGenerator++));
  // This will print that the Student Constructor was called
  // Then the GradStudent Constructor was called
  regList.add(new GradStudent(idGenerator++, "comp sci"));
  regList.print();
}

int main() {
  testLinkedList();
  testSet();
  testMyArray();
  testSum();
  testMyInt();
  testStudents();

  std::cout << "\nthe end!\n";
}
