#pragma once
#ifndef __COMMANDFACTORY_HPP__
#define __COMMANDFACTORY_HPP__

#include <iostream>
#include <map>

#include "ACommand.hpp"
#include "Authenticator.hpp"
#include "commands/NickCommand.hpp"
#include "commands/NoCommand.hpp"
#include "commands/PassCommand.hpp"
#include "commands/UserCommand.hpp"
#include "commands/PrivCommand.hpp"

// BOT BONUS
#include "BotManager.hpp"
#include "botcmds/CallCommand.hpp"
#include "botcmds/DismissCommand.hpp"
#include "botcmds/RenameCommand.hpp"
#include "botcmds/GrantCommand.hpp"
#include "botcmds/RevokeCommand.hpp"
#include "botcmds/AliasCommand.hpp"
#include "botcmds/RmidCommand.hpp"
#include "botcmds/OpenCommand.hpp"
#include "botcmds/CloseCommand.hpp"
#include "botcmds/ViewCommand.hpp"
#include "botcmds/ReplyCommand.hpp"


typedef ACommand *( *funcPtr )( Authenticator *authenticator, std::string _args, int fd );

class CommandFactory {
 private:
 public:
  CommandFactory();
  ~CommandFactory();
  CommandFactory( CommandFactory const &src );
  CommandFactory &operator=( CommandFactory const &src );
  ACommand       *makeCommand( Authenticator *authenticator, int fd, std::string commandName, std::string args );
};

#endif
