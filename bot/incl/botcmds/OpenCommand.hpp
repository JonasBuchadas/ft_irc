#pragma once
#ifndef __OPENCOMMAND_HPP__
#define __OPENCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class OpenCommand : public ACommand {
 private:
 public:
  OpenCommand( BotManager *BotManager, std::string args, int fd );
  ~OpenCommand();
  OpenCommand( OpenCommand const &src );
  OpenCommand &operator=( OpenCommand const &src );
  std::string  execute() const;
};

#endif
