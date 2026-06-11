#include "RPN.hpp"

int main(int ac, string *av) {

  if (ac != 2) {
    std::cerr << "Error" << std::endl;
    return ARG_LEN;
  }

  RPN rpn;
  try {
    std::cout << rpn.calc(av[1]) << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return ARG_VAL;
  }
  return OK;
}