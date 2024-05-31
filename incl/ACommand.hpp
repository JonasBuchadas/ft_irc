#pragma once
#ifndef __ACOMMAND_HPP__
#define __ACOMMAND_HPP__

#include <iostream>
#include <map>

#include "Authenticator.hpp"
#include "ChannelManager.hpp"

struct PreparedResponse {
  std::string      response;
  std::vector<int> recipients;
};

class ACommand {
 private:
  const std::string _name;

 protected:
  Authenticator  *_authenticator;
  ChannelManager *_channelManager;
  int             _userFD;
  std::string     _args;

 public:
  ACommand( Authenticator *authenticator, ChannelManager *channelManager );
  ACommand( std::string name, Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd );
  virtual ~ACommand();
  ACommand( ACommand const &src );
  ACommand &operator=( ACommand const &src );

  virtual PreparedResponse execute() const = 0;
};

#endif
