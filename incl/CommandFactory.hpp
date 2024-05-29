#pragma once
#ifndef __COMMANDFACTORY_HPP__
#define __COMMANDFACTORY_HPP__

#include <iostream>
#include <map>

#include "ACommand.hpp"
#include "Authenticator.hpp"
#include "ChannelManager.hpp"
#include "commands/NickCommand.hpp"
#include "commands/NoCommand.hpp"
#include "commands/PassCommand.hpp"
#include "commands/UserCommand.hpp"
#include "commands/PrivCommand.hpp"
#include "commands/JoinCommand.hpp"

typedef ACommand *( *funcPtr )( Authenticator *authenticator, ChannelManager *channelmanager, std::string _args, int fd );

class CommandFactory {
 private:
 public:
  CommandFactory();
  ~CommandFactory();
  CommandFactory( CommandFactory const &src );
  CommandFactory &operator=( CommandFactory const &src );
  ACommand       *makeCommand( Authenticator *authenticator, ChannelManager *channelmanager, int fd, std::string commandName, std::string args );
};

#endif
