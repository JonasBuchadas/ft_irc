#pragma once
#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <iostream>
#include <sstream>
#include <vector>

#include "Message.hpp"
#include "User.hpp"

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
