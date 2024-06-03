#pragma once
#ifndef __MODECOMMAND_HPP__
#define __MODECOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class ModeCommand : public ACommand {
 private:
 public:
  ModeCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  ~ModeCommand();
  ModeCommand( ModeCommand const &src );
  ModeCommand     &operator=( ModeCommand const &src );
  PreparedResponse execute() const;
};

#endif
