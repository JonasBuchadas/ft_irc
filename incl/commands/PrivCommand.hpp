#pragma once
#ifndef __PRIVCOMMAND_HPP__
#define __PRIVCOMMAND_HPP__

#include <arpa/inet.h>
#include <stdlib.h>

#include <iostream>

#include "ACommand.hpp"

class PrivCommand : public ACommand {
 private:
 public:
  PrivCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd );
  ~PrivCommand();
  PrivCommand( PrivCommand const &src );
  PrivCommand     &operator=( PrivCommand const &src );
  PreparedResponse execute() const;
};

#endif
