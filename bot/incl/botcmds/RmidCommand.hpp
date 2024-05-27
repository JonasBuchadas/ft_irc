#pragma once
#ifndef __RMIDCOMMAND_HPP__
#define __RMIDCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class RmidCommand : public ACommand {
 private:
 public:
  RmidCommand( BotManager *BotManager, std::string args, int fd );
  ~RmidCommand();
  RmidCommand( RmidCommand const &src );
  RmidCommand &operator=( RmidCommand const &src );
  std::string  execute() const;
};

#endif
