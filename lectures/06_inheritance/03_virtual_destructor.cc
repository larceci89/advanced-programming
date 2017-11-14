// Main message: always mark the destructor of a parent class as VIRTUAL
#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  ~Base() { std::cout << "~Base\n"; }
// virtual ~Base() { std::cout << "~Base\n"; }	// this is what to use
};

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
  //define and immediately destroy the derived class
  { Derived d; }

  std::cout << "\n\npointers\n";
  //now a new Derived element, which is destroyed
  Base* p = new Derived;
  delete p;
  //here only the destructor of Base is called!
  //to make it work, we have to mark the Base destructor as "virtual"

  return 0;
}
