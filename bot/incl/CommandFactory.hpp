#pragma once
#ifndef __COMMANDFACTORY_HPP__
#define __COMMANDFACTORY_HPP__

#include <iostream>
#include <map>

#include "ACommand.hpp"
#include "BotManager.hpp"

#include "botcmds/AcceptCommand.hpp"
#include "botcmds/AnswerCommand.hpp"
#include "botcmds/AskCommand.hpp"
#include "botcmds/CloseCommand.hpp"
#include "botcmds/InviteCommand.hpp"
#include "botcmds/NickCommand.hpp"
#include "botcmds/NoCommand.hpp"
#include "botcmds/RemoveCommand.hpp"
#include "botcmds/ReplyCommand.hpp"
#include "botcmds/ViewCommand.hpp"


typedef ACommand *( *funcPtr )( BotManager *BotManager, std::string _args, std::string nick );

class CommandFactory {
 private:
 public:
  CommandFactory();
  ~CommandFactory();
  CommandFactory( CommandFactory const &src );
  CommandFactory &operator=( CommandFactory const &src );
  ACommand       *makeCommand( std::string commandName, BotManager *BotManager, std::string args, std::string nick );
};

#endif
