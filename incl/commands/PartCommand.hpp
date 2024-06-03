#pragma once
#ifndef __PARTCOMMAND_HPP__
#define __PARTCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class PartCommand : public ACommand {
 private:
 public:
  PartCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  ~PartCommand();
  PartCommand( PartCommand const &src );
  PartCommand     &operator=( PartCommand const &src );
  PreparedResponse execute() const;
};

#endif
