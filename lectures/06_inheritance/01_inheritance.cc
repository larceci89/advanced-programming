/* struct Dog : public/private/protected Animal
   the semicolon means we use class inheritance: it means that Dog has
   an arrow pointing to the parent class Animal

   one can exploit the definition of parent class, to define functions that;
   take Animal as type in input, without template
*/
#include <iostream>
#include <ap_error.h>

struct Animal {
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    if (weight < 0)
      AP_error("invalid weight:", w);
  }

  Animal() : Animal{0, 0} {}  // delegating constructor

  void speak() const noexcept { std::cout << "Unknown\n"; }
  void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }
};

struct Dog : public Animal {
  void speak() const noexcept { std::cout << "Bau\n"; }
  Dog() = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}
};

// initialization top to bottom: top = parent, bottom = children
struct Snake : public Animal {
  bool dangerous;
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {}
  Snake(const bool b) : Animal{}, dangerous{b} {}
  void info() const noexcept {
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept { std::cout << "ssss\n"; }
};

inline void newline() noexcept {
  std::cout << std::endl;
}

void print_animal(const Animal& a) noexcept {
  std::cout << "through ref\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Dog d;
    d.info();
    d.speak();

    newline();

    Dog d1{0, 0.6};
    d1.info();
    d1.speak();

    newline();

    Snake s{true};
    s.info();
    s.speak();

    newline();

//   Animal* p = new Snake{ ... } ---> we are assigning the Animal type to Snake
//   note that polymorphism applies only to references and pointers, not objects
    Animal* p = new Snake{1, 2.3, false};
    std::cout << "through pointer\n";
    p->info();
    p->speak();
// this yields "Unknown"
// we are calling the function in the wrong struct: info is inside namespace Animal, not Snake
// we need something more: file 02

    delete p;

    newline();

    print_animal(s);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
