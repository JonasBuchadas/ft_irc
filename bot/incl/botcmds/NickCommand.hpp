#pragma once
#ifndef __NICKCOMMAND_HPP__
#define __NICKCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class NickCommand : public ACommand {
 private:
 public:
  NickCommand( BotManager *BotManager, std::string args, std::string nick );
  ~NickCommand();
  NickCommand( NickCommand const &src );
  NickCommand &operator=( NickCommand const &src );
  std::string  execute() const;
};

#endif
