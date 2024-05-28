#pragma once
#ifndef __NOCOMMAND_HPP__
#define __NOCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class NoCommand : public ACommand {
 private:
 public:
  NoCommand( BotManager *BotManager, std::string args, std::string nick );
  ~NoCommand();
  NoCommand( NoCommand const &src );
  NoCommand  &operator=( NoCommand const &src );
  std::string execute() const;
};

#endif
