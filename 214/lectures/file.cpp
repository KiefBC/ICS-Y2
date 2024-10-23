enum class Color { RED, GREEN, BLUE };

class Fruit {
 protected:
  const Color color;

 public:
  Fruit(Color newColor) : color(newColor){};
};

class Banana : public Fruit {
  Banana() : Fruit(Color::BLUE) {}
};

int main() {}
