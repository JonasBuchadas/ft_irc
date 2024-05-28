#pragma once
#ifndef __CLOSECOMMAND_HPP__
#define __CLOSECOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class CloseCommand : public ACommand {
 private:
 public:
  CloseCommand( BotManager *BotManager, std::string args, std::string nick );
  ~CloseCommand();
  CloseCommand( CloseCommand const &src );
  CloseCommand &operator=( CloseCommand const &src );
  std::string  execute() const;
};

#endif
