#pragma once
#ifndef __REVOKECOMMAND_HPP__
#define __REVOKECOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class RevokeCommand : public ACommand {
 private:
 public:
  RevokeCommand( BotManager *BotManager, std::string args, int fd );
  ~RevokeCommand();
  RevokeCommand( RevokeCommand const &src );
  RevokeCommand &operator=( RevokeCommand const &src );
  std::string  execute() const;
};

#endif
