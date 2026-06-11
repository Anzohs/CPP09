#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN &other) { (void)other; }
RPN RPN::operator=(const RPN &other) { (void)other; return *this; }
RPN::~RPN() {}

int RPN::calc(const std::string &expr) {
  std::stack<int> stack;
  std::istringstream ss(expr);
  std::string token;

  while (ss >> token) {
    if (token.size() == 1 && std::string("+-*/").find(token[0]) != std::string::npos) {
      if (stack.size() < 2)
        throw std::runtime_error("Error");

      int b = stack.top(); stack.pop();
      int a = stack.top(); stack.pop();

      if (token == "+") stack.push(a + b);
      else if (token == "-") stack.push(a - b);
      else if (token == "*") stack.push(a * b);
      else if (token == "/") {
        if (b == 0) throw std::runtime_error("Error");
        stack.push(a / b);
      }
    }
    else {
      if (token.size() != 1 || !std::isdigit(token[0]))
        throw std::runtime_error("Error");
      stack.push(token[0] - '0');
    }
  }

  if (stack.size() != 1)
    throw std::runtime_error("Error");

  return stack.top();
}