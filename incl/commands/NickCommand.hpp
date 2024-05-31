#pragma once
#ifndef __NICKCOMMAND_HPP__
#define __NICKCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class NickCommand : public ACommand {
 private:
 public:
  NickCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd );
  ~NickCommand();
  NickCommand( NickCommand const &src );
  NickCommand     &operator=( NickCommand const &src );
  PreparedResponse execute() const;
};

#endif
