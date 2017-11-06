#include <iostream>
#include <string>

struct S {
  int a;
  double b;
  std::string s;  // default ctor of string set s to empty string
  // S() = default;		//this is useless, the compiler does it anyway
};

int main() {
  S s1;  // calls default constructor

  S s2{1, 2.3, "alberto"};  // if there are no custom ctors I can
                            // directly initialize the members. Note
                            // that I need access (i.e. they must be
                            // public)
  S s3{};                   // calls {} on each member: S s3 { {}, {}, {} };

  std::cout << s1.a << "--" << s1.b << "--" << s1.s << "\n";
  std::cout << s2.a << "--" << s2.b << "--" << s2.s << "\n";
  std::cout << s3.a << "--" << s3.b << "--" << s3.s << "\n";

struct S_built_in {
  int a;
  double b;
  char c;
  // S_built_in() = default;
};

struct S_custom_type {
  std::string s;
  // S_custom_type() = default;
};

int main() {
  S_built_in s1;    // calls default constructor
  S_built_in s2{};  // calls {} on each member
  std::cout << s1.a << "--" << s1.b << "--" << s1.c << "\n";
  std::cout << s2.a << "--" << s2.b << "--" << s2.c << "\n";

  S_custom_type sc;  // calls default constructor
  std::cout << sc.s << std::endl;

  return 0;
}
