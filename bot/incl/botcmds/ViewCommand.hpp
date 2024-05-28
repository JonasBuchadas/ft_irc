#pragma once
#ifndef __VIEWCOMMAND_HPP__
#define __VIEWCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class ViewCommand : public ACommand {
 private:
 public:
  ViewCommand( BotManager *BotManager, std::string args, std::string nick );
  ~ViewCommand();
  ViewCommand( ViewCommand const &src );
  ViewCommand &operator=( ViewCommand const &src );
  std::string  execute() const;
};

#endif
