#pragma once
#ifndef __ACOMMAND_HPP__
#define __ACOMMAND_HPP__

#include <iostream>
#include <map>
#include <sstream>

#include "ChannelManager.hpp"
#include "Message.hpp"
#include "UserManager.hpp"

struct PreparedResponse {
  std::string      response;
  std::vector<int> recipients;
};

class ACommand {
 private:
  const std::string _name;

 protected:
  UserManager    *_userManager;
  ChannelManager *_channelManager;
  int             _userFD;
  std::string     _args;

 public:
  ACommand( UserManager *userManager, ChannelManager *channelManager );
  ACommand( std::string name, UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  virtual ~ACommand();
  ACommand( ACommand const &src );
  ACommand &operator=( ACommand const &src );

  virtual PreparedResponse execute() const = 0;
  PreparedResponse         serverResponse( int code, const std::string &msg ) const;
};

#endif
