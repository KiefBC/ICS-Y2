#pragma once

class MyVector {
private:
  int m_size;
  double *pItems;
  void checkRange(int index) const;

public:
  MyVector(int size = 0);
  ~MyVector() { delete[] pItems; }
  int size() const;
  double get(int index) const;
  void set(int index, double value);
};
