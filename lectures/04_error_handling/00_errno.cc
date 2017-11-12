// it gives NO error, but the result is nan
// errno contains the error number "33"
#include <cmath>
#include <iostream>

int main() {
  double d = sqrt(-9);
  std::cout << d << std::endl;
  std::cout << errno << " " << d << std::endl;
  return 0;
}
