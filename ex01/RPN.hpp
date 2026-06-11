#pragma once
#include <stack>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>


typedef char* string;


typedef enum ERRORS {
  OK,
  ARG_LEN,
  ARG_VAL
} ERRORS;

class RPN {
  public:
  RPN();
  ~RPN();
  RPN(const RPN&);
  RPN operator=(const RPN&);

  int calc(const std::string &expr);
};