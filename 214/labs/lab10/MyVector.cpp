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

  this->m_size = size;
}

void MyVector::checkRange(int index) const {
  if (index < 0 || index >= m_size) {
    throw std::out_of_range("MyVector::checkRange(): index out of range");
  }
}

int MyVector::size() const { return m_size; }

double MyVector::get(int index) const {
  checkRange(index); // check if index is out of bounds
  std::cout << "Returning item " << index << ": " << pItems[index] << "\n";
  return pItems[index];
}

void MyVector::set(int index, double value) {
  checkRange(index); // check if index is out of bounds
  pItems[index] = value;
}
