#pragma once
#ifndef __KICKCOMMAND_HPP__
#define __KICKCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class KickCommand : public ACommand {
 private:
 public:
  KickCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  ~KickCommand();
  KickCommand( KickCommand const &src );
  KickCommand     &operator=( KickCommand const &src );
  PreparedResponse execute() const;
};

#endif
