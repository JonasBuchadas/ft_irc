#pragma once
#ifndef __COMMANDFACTORY_HPP__
#define __COMMANDFACTORY_HPP__

#include <iostream>
#include <map>

#include "ACommand.hpp"
#include "ChannelManager.hpp"
#include "UserManager.hpp"
#include "commands/InviteCommand.hpp"
#include "commands/JoinCommand.hpp"
#include "commands/KickCommand.hpp"
#include "commands/LogoutCommand.hpp"
#include "commands/TopicCommand.hpp"
#include "commands/ModeCommand.hpp"
#include "commands/NamesCommand.hpp"
#include "commands/NickCommand.hpp"
#include "commands/NoCommand.hpp"
#include "commands/PartCommand.hpp"
#include "commands/PassCommand.hpp"
#include "commands/PrivCommand.hpp"
#include "commands/UserCommand.hpp"

typedef ACommand *( *funcPtr )( UserManager *userManager, ChannelManager *channelmanager, std::string _args, int fd );

class CommandFactory {
 private:
  UserManager    *_userManager;
  ChannelManager *_channelManager;
  CommandFactory();

 public:
  CommandFactory( const char *password );
  ~CommandFactory();
  CommandFactory( CommandFactory const &src );
  CommandFactory &operator=( CommandFactory const &src );
  ACommand       *makeCommand( int fd, std::string commandName, std::string args, bool internal );
};

#endif
