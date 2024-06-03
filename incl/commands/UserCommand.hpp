#pragma once
#ifndef __USERCOMMAND_HPP__
#define __USERCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class UserCommand : public ACommand {
 private:
 public:
  UserCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  ~UserCommand();
  UserCommand( UserCommand const &src );
  UserCommand     &operator=( UserCommand const &src );
  PreparedResponse execute() const;
};

#endif
