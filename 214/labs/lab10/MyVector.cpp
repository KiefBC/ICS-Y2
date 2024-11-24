#include "MyVector.h"
#include <iostream>
#include <stdexcept>

MyVector::MyVector(int size) : m_size(size) {
  if (size < 0) {
    throw std::length_error("MyVector::MyVector(): size must be >= 0");
  }

  if (size == 0) {
    pItems = nullptr;
  } else {
    pItems = new double[size];
  }
}

MyVector::MyVector(const std::initializer_list<double> &list)
    : MyVector(static_cast<int>(list.size())) {
  if (list.size() > 0) {
    pItems = new double[list.size()];
    int i = 0;
    for (auto &element : list) {
      pItems[i] = element;
      i++;
    }
  }
}

MyVector::MyVector(const MyVector &other) : MyVector(other.size()) {
  for (int i = 0; i < other.size(); i++) {
    pItems[i] = other.get(i);
  }
}

void MyVector::checkRange(int index) const {
  if (index < 0 || index >= m_size) {
    throw std::out_of_range("MyVector::checkRange(): index out of range");
  }
}

double MyVector::get(int index) const {
  checkRange(index);
  return pItems[index];
}

void MyVector::set(int index, double value) {
  checkRange(index);
  pItems[index] = value;
}

std::ostream &operator<<(std::ostream &os, const MyVector &myVector) {
  os << "[";
  for (int i = 0; i < myVector.size(); i++) {
    os << myVector.get(i);
    if (i < myVector.size() - 1) {
      os << ", ";
    }
  }
  os << "]";
  return os;
}

MyVector &MyVector::operator=(const MyVector &other) {
  // Check for self-assignment
  if (this == &other) {
    return *this;
  }

  // Delete the old array
  delete[] pItems;

  // Copy the size
  m_size = other.size();

  // Allocate if necessary
  if (m_size == 0) {
    pItems = nullptr;
  } else {
    pItems = new double[m_size];

    // Copy the elements
    for (int i = 0; i < m_size; i++) {
      pItems[i] = other.get(i);
    }
  }

  return *this;
}

double &MyVector::operator[](int index) {
  checkRange(index);
  return pItems[index];
}

double &MyVector::operator[](int index) const {
  checkRange(index);
  return pItems[index];
}

void MyVector::runner() {
  std::cout << "\n";
  MyVector v{1.1, 2.2};
  std::cout << v[0] << '\n'; // should output 1.1
  v[0] = 9.9;
  std::cout << v[0] << '\n'; // should output 9.9
  const MyVector constVec{3.3, 4.4};
  std::cout << constVec[0]; // should output 3.3
  std::cout << "\n\n";
}
