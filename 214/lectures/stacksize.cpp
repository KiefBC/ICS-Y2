// Objectives:
//   - Illustrate the difference between std::vector size() and capcity()
//   - Create an IntStack that uses the concept of size and capacity
//   - Throw exceptions when appropriate
//   - Template IntStack with a type: Stack<T>
//   - Add a non-type parameter to allow us to choose the capacity: Stack<T, CAP>


#include <iostream>
#include <vector>

// a Cents class that we can use for testing custom types
class Cents {
private:
    int value{ 0 };
public:
    Cents(int val = 0) : value{ val } {
    }

    Cents(const Cents& c2) {
        static int count{ 0 };
        ++count;
        value = c2.value;
        std::cout << "Copy constructor called.\n" << count << std::endl;
    }

    int getValue() const { return value; }
};

// allows us to output a cent to the console
std::ostream & operator<<(std::ostream & out, const Cents & c) {
    out << "[cents: " << c.getValue() << "]";
    return out;
}

// encapsulate a stack built with a fixed array of ints
template <typename T, int N>
class Stack {
private:
    static const int capacity{ N };  // the capacity of the array
    T elements[capacity];          // the array itself
    int size{ 0 };                   // the num of elements in the array
public:
    void push(T value) {
        if (size == capacity) {
            throw std::out_of_range("Stack is full");
        }
        elements[size++] = value;
    }

    T pop() {
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[--size];
    }
};

// template <typename T>
// void printVectorStats(const std::vector<T>& v) {
//     std::cout << "size: " << v.size() << " capacity: " << v.capacity() << std::endl;
// }

int main()
{

    //std::vector<Cents> v;
    //v.reserve(20);
    //for (int i = 0; i < 20; i++) {
    //    v.push_back(i);
    //    printVectorStats(v);
    //}

    Stack<Cents, 10> s;
    for (int i = 0; i < 6; i++) {
        s.push(i);
    }

    try {
        for (int i = 0; i < 6; i++) {
            std::cout << s.pop() << std::endl;
        }
    }
    catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }
    }
