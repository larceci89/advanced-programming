// look at the 911 lines of code
#include <iostream>
#include <ap_error.h>

class Animal {
  unsigned int age;
  double weight;

 public:
  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    if (weight < 0)
      AP_error("invalid weight:", w);
  }

  Animal() : Animal{0, 0} {}  // delegating constructor

  virtual void speak() const = 0;
  virtual void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }

  virtual ~Animal() {}
};

class Dog : public Animal {
 public:
  void speak() const noexcept override { std::cout << "Bau\n"; }
  Dog() = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}
};

class Snake : public Animal {
  bool dangerous;

 public:
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {}
  Snake(const bool b) : Animal{}, dangerous{b} {}
  void info() const noexcept override {
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept override { std::cout << "ssss\n"; }
};

inline void newline() noexcept {
  std::cout << std::endl;
}

class DangerousSnake : public Snake {
 public:
  DangerousSnake(const unsigned int a, const double w) : Snake{a, w, true} {}
  DangerousSnake() : Snake{true} {}
};

class NonDangerousSnake : public Snake {
 public:
  NonDangerousSnake(const unsigned int a, const double w)
      : Snake{a, w, false} {}
  NonDangerousSnake() : Snake{false} {}
};

struct Python : public NonDangerousSnake {};

using Anaconda = DangerousSnake;

void print_animal(const Animal& a) noexcept {
  a.info();
  a.speak();
  // if got a DangerousSnake call 911
  if (dynamic_cast<const DangerousSnake*>(&a))
    std::cout << "call 911...\n";
}

int main() {
  try {
    Python s;
    print_animal(s);

    newline();

    // Animal* p = new DangerousSnake{1, 2.3};
    Animal* p = new Anaconda{1, 2.3};

    print_animal(*p);
    delete p;

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
