#pragma once
#ifndef __JOINCOMMAND_HPP__
#define __JOINCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class JoinCommand : public ACommand {
 private:
 public:
  JoinCommand();
  ~JoinCommand();
  JoinCommand( JoinCommand const &src );
  JoinCommand &operator=( JoinCommand const &src );
  std::string  execute() const;
};

#endif
