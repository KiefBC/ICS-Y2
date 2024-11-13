#include <iostream>
#include <vector>

class Cents {
private:
  int value;

public:
  Cents(int val = 0) : value(val) { std::cout << "Cents.ctor()\n"; }

  Cents(const Cents &c2) {
    std::cout << "Cents.copy_ctor()\n";
    value = c2.value;
  }

  Cents& operator=(const Cents& c2) {
    std::cout << "Cents.copy_assignment()\n";
    // value = c2.value;
    return *this;
  }
};

void test(Cents c) { std::cout << "test()\n"; }

int main() {
  // Cents nickel(5); // init
  // Cents c2 = nickel;
  // Cents c3(nickel);
  // Cents c4{nickel};
  //test(nickel); // pass by value
  // std::vector<Cents> v{ Cents(10), Cents(5) };

  // Cents c2;
  // c2 = nickel; // assignment

  Cents nickel(5);
  Cents c2;
  c2 = nickel; // assignment

  int x;
  int y;
  x = y = 5;

  std::cout << 5 << 6;
}
