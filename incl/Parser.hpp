#pragma once
#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <iostream>
#include <sstream>
#include <vector>

#include "Server.hpp"
#include "User.hpp"

struct ParsedMsg {
  std::string commandName;
  std::string args;
  bool        internal;
};

class Parser {
 private:
 public:
  Parser();
  ~Parser();
  Parser( Parser const &src );
  Parser                &operator=( Parser const &src );
  std::vector<ParsedMsg> parseMsg( UnparsedMsg msg );
};

#endif
