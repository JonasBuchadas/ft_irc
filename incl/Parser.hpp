#pragma once
#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <iostream>
#include <map>
#include <sstream>

#include "User.hpp"

struct ParsedMsg {
  std::string commandName;
  std::string args;
};

class Parser {
 private:
 public:
  Parser();
  ~Parser();
  Parser( Parser const &src );
  Parser   &operator=( Parser const &src );
  ParsedMsg parseMsg( std::string str );
};

#endif
