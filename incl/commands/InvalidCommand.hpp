#pragma once
#ifndef __INVALIDCOMMAND_HPP__
#define __INVALIDCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class InvalidCommand : public ACommand {
 private:
 public:
  InvalidCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  ~InvalidCommand();
  InvalidCommand( InvalidCommand const &src );
  InvalidCommand  &operator=( InvalidCommand const &src );
  PreparedResponse execute() const;
};

#endif
