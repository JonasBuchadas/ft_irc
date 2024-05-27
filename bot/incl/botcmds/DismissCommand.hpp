#pragma once
#ifndef __DISMISSCOMMAND_HPP__
#define __DISMISSCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class DismissCommand : public ACommand {
 private:
 public:
  DismissCommand( BotManager *BotManager, std::string args, int fd );
  ~DismissCommand();
  DismissCommand( DismissCommand const &src );
  DismissCommand &operator=( DismissCommand const &src );
  std::string  execute() const;
};

#endif
