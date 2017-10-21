#include "ap_error.h"
#include <assert.h>
#include <cmath>
#include <iostream>

// implment a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);

int main() {
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    double d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

double square_root(const double d) {
  // test the pre-conditions
  // assert(d >= 0 && d <= 50);
  // AP_assert(d>=0 && d<=50, "d should be in the range [0,50]", "d=",d);
  AP_assert(d >= 0 && d <= 50, NotInRange(0, 50, d));
  return sqrt(d);
}
