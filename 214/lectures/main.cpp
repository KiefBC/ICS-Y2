#include <iostream>

int main() {
  int x{5};
  std::cout << x << std::endl;

  int* ptr{&x};
  std::cout << ptr << std::endl;

  std::cout << *ptr << std::endl;

  int y{6};
  ptr = &y;
  int& ref{y};
  std::cout << "Y: " << ref << std::endl;
  std::cout << ptr << std::endl;
  std::cout << *ptr << std::endl;

  *ptr = 8;
  std::cout << ptr << std::endl;
  std::cout << *ptr << std::endl;
}
