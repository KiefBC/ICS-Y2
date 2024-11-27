#pragma once
#include <iostream>
#include <vector>

/// @brief A class that represents a vector of elements
/// @tparam T The type of the elements in the vector
template <typename T> class MyVector {
private:
  int m_size; // number of elements in the vector
  int m_capacity; // number of elements the vector can hold
  T *pItems; // pointer to the dynamically allocated array
  void checkRange(int index) const; // checks if the index is in range

public:
  /// @brief Constructor for MyVector that initializes the vector with a given
  /// size and initializes all elements to 0
  /// @param size The size of the vector
  explicit MyVector(int size = 0);

  /// @brief Constructor for MyVector that initializes the vector with a given
  /// initializer list
  /// @param list The initializer list
  MyVector(const std::initializer_list<T> &list);

  /// @brief Copy constructor for MyVector
  /// @param other The MyVector to copy
  MyVector(const MyVector<T> &other);

  /// @brief Destructor for MyVector
  ~MyVector() { delete[] pItems; }

  /// @brief Returns the size of the vector
  /// @return The size of the vector
  int size() const { return m_size; };

  /// @brief Returns the element at the given index
  /// @param index The index of the element to return
  /// @return The element at the given index
  T get(int index) const;

  /// @brief Sets the element at the given index to the given value
  /// @param index The index of the element to set
  /// @param value The value to set the element to
  void set(int index, T value);

  /// @brief Runs the runner function
  void runner();

  /// @brief Assignment operator for MyVector
  /// @param other The MyVector to assign
  /// @return The assigned MyVector
  MyVector<T> &operator=(const MyVector<T> &other);

  /// @brief Returns the element at the given index
  /// @param index The index of the element to return
  /// @return The element at the given index
  T &operator[](int index);

  /// @brief Returns the element at the given index (const version)
  /// @param index The index of the element to return
  /// @return The element at the given index
  const T &operator[](int index) const;

  /// @brief Returns the capacity of the vector
  /// @return The capacity of the vector
  int capacity() const { return m_capacity; }

  /// @brief Reserves memory for the vector
  /// @param newCapacity The new capacity of the vector
  void reserve(int newCapacity);

  /// @brief Resizes the vector
  /// @param newSize The new size of the vector
  void resize(int newSize);

  /// @brief Adds an element to the end of the vector
  /// @param value The value to add to the end of the vector
  void push_back(T value);

  /// @brief Removes the last element from the vector
  /// @return The last element from the vector
  T pop_back();

  /// @brief Outputs the vector to the given stream
  /// @param os The stream to output to
  /// @param vec The MyVector to output
  /// @return The stream
  friend std::ostream &operator<<(std::ostream &os, const MyVector<T> &vec) {
    os << "[";
    for (int i = 0; i < vec.size(); i++) {
      os << vec.get(i);
      if (i < vec.size() - 1) {
        os << ", ";
      }
    }
    os << "]";
    return os;
  }
};

template <typename T>
MyVector<T>::MyVector(int size) : m_size(size), m_capacity(size) {
  if (size < 0) {
    throw std::length_error("MyVector::MyVector(): size must be >= 0");
  }

  if (size == 0) {
    pItems = nullptr;
  } else {
    pItems = new T[size];
  }
}

template <typename T>
MyVector<T>::MyVector(const std::initializer_list<T> &list)
    : MyVector(static_cast<int>(list.size())) {
  if (list.size() > 0) {
    pItems = new T[list.size()];
    int i = 0;
    for (auto &element : list) {
      pItems[i] = element;
      i++;
    }
  }
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &other) : MyVector(other.size()) {
  for (int i = 0; i < other.size(); i++) {
    pItems[i] = other.get(i);
  }
}

template <typename T> void MyVector<T>::checkRange(int index) const {
  if (index < 0 || index >= m_size) {
    throw std::out_of_range("MyVector::checkRange(): index out of range");
  }
}

template <typename T> T MyVector<T>::get(int index) const {
  checkRange(index);
  return pItems[index];
}

template <typename T> void MyVector<T>::set(int index, T value) {
  checkRange(index);
  pItems[index] = value;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &other) {
  if (this == &other) {
    return *this;
  }

  delete[] pItems;
  m_size = other.size();
  m_capacity = other.size();

  if (m_size == 0) {
    pItems = nullptr;
  } else {
    pItems = new T[m_size];
    for (int i = 0; i < m_size; i++) {
      pItems[i] = other.get(i);
    }
  }

  return *this;
}

template <typename T> T &MyVector<T>::operator[](int index) {
  checkRange(index);
  return pItems[index];
}

template <typename T> const T &MyVector<T>::operator[](int index) const {
  checkRange(index);
  return pItems[index];
}

template <typename T> void MyVector<T>::runner() {
  std::cout << "\n";
  MyVector<T> v{static_cast<T>(1.1), static_cast<T>(2.2)};
  std::cout << v[0] << '\n'; // should output 1.1
  v[0] = static_cast<T>(9.9);
  std::cout << v[0] << '\n'; // should output 9.9
  const MyVector<T> constVec{static_cast<T>(3.3), static_cast<T>(4.4)};
  std::cout << constVec[0]; // should output 3.3
  std::cout << "\n\n";
}

template <typename T> void MyVector<T>::reserve(int newCapacity) {
  if (newCapacity <= m_capacity) {
    return;
  }

  T *newItems = new T[newCapacity];

  if (pItems != nullptr) {
    for (int i = 0; i < m_size; i++) {
      newItems[i] = pItems[i];
    }
    delete[] pItems;
  }

  pItems = newItems;
  m_capacity = newCapacity;
}

template <typename T> void MyVector<T>::resize(int newSize) {
  if (newSize < 0) {
    throw std::length_error("MyVector::resize(): newSize must be >= 0");
  }

  if (newSize > m_capacity) {
    reserve(newSize);
  }

  if (newSize > m_size) {
    for (int i = m_size; i < newSize; i++) {
      pItems[i] = T();
    }
  }

  m_size = newSize;
}

template <typename T> void MyVector<T>::push_back(T value) {
  if (m_capacity == 0) {
    reserve(8);
  } else if (m_size == m_capacity) {
    reserve(m_capacity * 2);
  }

  pItems[m_size] = value;
  m_size++;
}

template <typename T> T MyVector<T>::pop_back() {
  if (m_size == 0) {
    throw std::runtime_error("cannot pop_back() an empty vector");
  }

  m_size--;
  return pItems[m_size];
}
