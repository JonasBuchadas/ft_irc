#pragma once
#ifndef __INVALIDCOMMAND_HPP__
#define __INVALIDCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class InvalidCommand : public ACommand {
 private:
 public:
  InvalidCommand( std::string args, std::string nick );
  ~InvalidCommand();
  InvalidCommand( InvalidCommand const &src );
  InvalidCommand &operator=( InvalidCommand const &src );
  std::string     execute() const;
};

#endif
