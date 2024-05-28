#pragma once
#ifndef __REMOVECOMMAND_HPP__
#define __REMOVECOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class RemoveCommand : public ACommand {
 private:
 public:
  RemoveCommand( BotManager *BotManager, std::string args, std::string nick );
  ~RemoveCommand();
  RemoveCommand( RemoveCommand const &src );
  RemoveCommand &operator=( RemoveCommand const &src );
  std::string  execute() const;
};

#endif
