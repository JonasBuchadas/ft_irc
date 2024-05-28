#pragma once
#ifndef __ASKCOMMAND_HPP__
#define __ASKCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class AskCommand : public ACommand {
 private:
 public:
  AskCommand( BotManager *botManager, std::string args, std::string nick );
  ~AskCommand();
  AskCommand( AskCommand const &src );
  AskCommand &operator=( AskCommand const &src );
  std::string  execute() const;
};

#endif
