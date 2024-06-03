#pragma once
#ifndef __NamesCommand_HPP__
#define __NamesCommand_HPP__

#include <iostream>

#include "ACommand.hpp"

class NamesCommand : public ACommand {
 private:
 public:
  NamesCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  ~NamesCommand();
  NamesCommand( NamesCommand const &src );
  NamesCommand    &operator=( NamesCommand const &src );
  PreparedResponse execute() const;
};

#endif
