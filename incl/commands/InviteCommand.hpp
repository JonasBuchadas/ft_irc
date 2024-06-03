#pragma once
#ifndef __INVITECOMMAND_HPP__
#define __INVITECOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class InviteCommand : public ACommand {
 private:
 public:
  InviteCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  ~InviteCommand();
  InviteCommand( InviteCommand const &src );
  InviteCommand   &operator=( InviteCommand const &src );
  PreparedResponse execute() const;
};

#endif
