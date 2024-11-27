#include "MyVector.h"
#include <iostream>
#include <stdexcept>

MyVector::MyVector(int size) : m_size(size), m_capacity(size) {
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
  if (this == &other) {
    return *this;
  }

  delete[] pItems;
  m_size = other.size();
  m_capacity = other.size();

  if (m_size == 0) {
    pItems = nullptr;
  } else {
    pItems = new double[m_size];
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

void MyVector::reserve(int newCapacity) {
  // If requested capacity is less than or equal to current, do nothing
  if (newCapacity <= m_capacity) {
    return;
  }

  double *newItems = new double[newCapacity];

  // Copy existing elements if any
  if (pItems != nullptr) {
    for (int i = 0; i < m_size; i++) {
      newItems[i] = pItems[i];
    }
    delete[] pItems;
  }

  pItems = newItems;
  m_capacity = newCapacity;
}

void MyVector::resize(int newSize) {
  if (newSize < 0) {
    throw std::length_error("MyVector::resize(): newSize must be >= 0");
  }

  if (newSize > m_capacity) {
    reserve(newSize);
  }

  if (newSize > m_size) {
    for (int i = m_size; i < newSize; i++) {
      pItems[i] = 0.0;
    }
  }

  m_size = newSize;
}

void MyVector::push_back(double value) {
  if (m_capacity == 0) {
    reserve(8);
  } else if (m_size == m_capacity) {
    reserve(m_capacity * 2);
  }

  pItems[m_size] = value;
  m_size++;
}

double MyVector::pop_back() {
  if (m_size == 0) {
    throw std::runtime_error("cannot pop_back() an empty vector");
  }

  m_size--;
  return pItems[m_size];
}
