#include "../include/seven.hpp"
#include <iostream>

int main() {

  Seven seven1;
  Seven seven2(4, 6);
  Seven seven3({1, 2, 3});
  Seven seven4("654");

  std::cout << "seven1 = " << seven1 << "\n";
  std::cout << "seven2 = " << seven2 << "\n";
  std::cout << "seven3 = " << seven3 << "\n";
  std::cout << "seven4 = " << seven4 << "\n";

  Seven sum = seven3 + seven4;
  Seven diff = sum - seven3;

  std::cout << "seven3 + seven4 = " << sum << "\n";
  std::cout << "sum - seven3 = " << diff << "\n";

  std::cout << "seven3 == seven4? " << (seven3 == seven4 ? "yes" : "no")
            << std::endl;
  std::cout << "sum >= diff? " << (sum >= diff ? "yes" : "no") << std::endl;

  Seven copy = seven3;
  Seven moved = std::move(copy);

  std::cout << "copy after move = " << copy << "\n";
  std::cout << "moved = " << moved << "\n";

  return 0;
}