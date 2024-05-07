#include <iostream>

struct Foo {
  virtual ~Foo() {
    std::cout << "foo called\n";
  }
};

struct Bar : public Foo{
  ~Bar() {
    std::cout << "bar called\n";
  }
};

int main() {
  Foo *ff = new Bar();
  delete ff;
}
