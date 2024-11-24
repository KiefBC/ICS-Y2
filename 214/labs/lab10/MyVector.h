#pragma once
#include <iostream>

class MyVector {
private:
  int m_size;
  double *pItems;
  void checkRange(int index) const;

public:
  explicit MyVector(int size = 0);
  MyVector(const std::initializer_list<double> &list);
  MyVector(const MyVector &other);
  ~MyVector() { delete[] pItems; }
  int size() const { return m_size; };
  double get(int index) const;
  void set(int index, double value);
  void runner();
  friend std::ostream &operator<<(std::ostream &os, const MyVector &vec);
  MyVector &operator=(const MyVector &other);
};
