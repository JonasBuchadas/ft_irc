#pragma once
#ifndef __ACCEPTCOMMAND_HPP__
#define __ACCEPTCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class AcceptCommand : public ACommand {
 private:
 public:
  AcceptCommand( BotManager *BotManager, std::string args, std::string nick );
  ~AcceptCommand();
  AcceptCommand( AcceptCommand const &src );
  AcceptCommand &operator=( AcceptCommand const &src );
  std::string  execute() const;
};

#endif
