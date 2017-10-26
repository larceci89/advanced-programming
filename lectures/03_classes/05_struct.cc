/*	structs and classes are almost equivalent: the formers are public,
	while the latters are private (unless otherwise specified).
	Common use is to employ structs for blocks of data, and classes to
	implement customized functions. */
#include <iostream>

struct Point_s {
  double x;
  double y;
};

class Point_c {
  double x;
  double y;
};

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  Point_c pc;
  // pc.x =7.6; // error

  Point_s* p = &ps;

  p->x = 0.0;

  std::cout << p->y << std::endl;

  return 0;
}
