#pragma once
#include <iostream>

class MyVector {
private:
  int m_size;
  double *pItems;
  void checkRange(int index) const;

public:
  /// @brief Constructor for MyVector that initializes the vector with a given
  /// size and initializes all elements to 0
  /// @param size The size of the vector
  explicit MyVector(int size = 0);

  /// @brief Constructor for MyVector that initializes the vector with a given
  /// initializer list
  /// @param list The initializer list to initialize the vector with
  MyVector(const std::initializer_list<double> &list);

  /// @brief Copy constructor for MyVector
  /// @param other The MyVector to copy
  MyVector(const MyVector &other);

  /// @brief Destructor for MyVector
  ~MyVector() { delete[] pItems; }

  /// @brief Get the size of the vector
  /// @return The size of the vector
  int size() const { return m_size; };

  /// @brief Get the value at a given index
  /// @param index The index to get the value at
  /// @return The value at the given index
  double get(int index) const;

  /// @brief Set the value at a given index
  /// @param index The index to set the value at
  /// @param value The value to set
  void set(int index, double value);

  /// @brief A function that runs a loop to test the get and set functions
  void runner();

  /// @brief Overloaded << operator to print the vector
  /// @param os The output stream to print to
  /// @param vec The MyVector to print
  /// @return The output stream
  friend std::ostream &operator<<(std::ostream &os, const MyVector &vec);

  /// @brief Overloaded = operator to assign a MyVector to another MyVector
  /// @param other The MyVector to assign
  /// @return The assigned MyVector
  MyVector &operator=(const MyVector &other);

  /// @brief Overloaded [] operator to access the value at a given index
  /// @param index The index to access
  /// @return The value at the given index
  double &operator[](int index);

  /// @brief Overloaded [] operator to access the value at a given index (const
  /// version)
  /// @param index The index to access
  /// @return The value at the given index
  double &operator[](int index) const;
};
