#pragma once
#ifndef __LOGOUTCOMMAND_HPP__
#define __LOGOUTCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class LogoutCommand : public ACommand {
 private:
 public:
  LogoutCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd );
  ~LogoutCommand();
  LogoutCommand( LogoutCommand const &src );
  LogoutCommand   &operator=( LogoutCommand const &src );
  PreparedResponse execute() const;
};

#endif
