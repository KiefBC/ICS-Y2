#include <iostream>
#include <vector>

class Printable {
public:
  virtual void print() const = 0;
  virtual ~Printable() {}
};

class Saveable {
public:
  virtual void save() const = 0;
  virtual ~Saveable() {}
};

class Document : public Printable, public Saveable {
public:
  void print() const override { std::cout << "Document::print()" << std::endl; }
  virtual ~Document() {}
  virtual void save() const override {
    std::cout << "Document::save()" << std::endl;
  }
};

class Image : public Printable {
public:
  void print() const override { std::cout << "Image::print()" << std::endl; }
  virtual ~Image() {}
};

class PrintQeue {
private:
  std::vector<Printable *> printables;

public:
  void add(Printable *p) { printables.push_back(p); }
  void print() {
    for (auto *p : printables) {
      p->print();
    }
    printables.clear();
  }
};

class Point {
public:
  int x{0};
  int y{0};
};

void testSave(Saveable &s) { s.save(); }

int main() {
  Document doc;
  Image img;
  PrintQeue pq;

  doc.print();
  img.print();

  std::cout << "----------------" << std::endl;
  pq.add(&doc);
  pq.add(&img);
  testSave(doc);
  std::cout << "----------------" << std::endl;

  Point p1;
  p1.x = 10;
  p1.y = 20;

  Point p2 = p1;

  p1.x = 100;
  p1.y = 200;

  std::cout << "p1.x: " << p1.x << ", p1.y: " << p1.y << std::endl;
  std::cout << "p2.x: " << p2.x << ", p2.y: " << p2.y << std::endl;

  return 0;
}
