#pragma once
#ifndef __ALIASCOMMAND_HPP__
#define __ALIASCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class AliasCommand : public ACommand {
 private:
 public:
  AliasCommand( BotManager *botManager, std::string args, int fd );
  ~AliasCommand();
  AliasCommand( AliasCommand const &src );
  AliasCommand &operator=( AliasCommand const &src );
  std::string  execute() const;
};

#endif
