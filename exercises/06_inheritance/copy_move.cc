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

  Animal(const Animal& a) : Animal{a.age}, Animal{a.weight} {}
//copy assignment in the parent class
  Animal& operator=(const Animal& a){
	age = a.age;
	weight = a.weight;
	return *this;
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
  Snake(const Snake& s) : Animal{a}, dangerous{s.dangerous} {}

// copy_assignment --> function that returns a reference to the Snake element
  Snake& operator=(const Snake& s){
	//how to copy the Animal part: s1 = s2 is the same as calling s1.operator=(s2)
	Animal::operator=(s);
	dangerous = s.dangerous;
	return *this;
  }


  void speak() const noexcept override { std::cout << "ssss\n"; }
};

inline void newline() noexcept {
  std::cout << std::endl;
}

void print_animal(const Animal& a) noexcept {
  a.info();
  a.speak();
  std::cout << "\n\n";
}

int main() {
  try {
    Snake s{1, 2.3, true};

    Snake s1{s};
    print_animal(s1);

    Snake s2{std::move(s)};

    print_animal(s2);

    s = s1;

    print_animal(s);

    s2 = std::move(s1);

    print_animal(s2);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
