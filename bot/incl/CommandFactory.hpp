#pragma once
#ifndef __COMMANDFACTORY_HPP__
#define __COMMANDFACTORY_HPP__

#include <iostream>
#include <map>

#include "ACommand.hpp"
#include "botcmds/InvalidCommand.hpp"
#include "botcmds/InviteCommand.hpp"
#include "botcmds/NamesCommand.hpp"
#include "botcmds/ShootCommand.hpp"

typedef ACommand *( *funcPtr )( std::string _args, std::string nick );

class CommandFactory {
 private:
 public:
  CommandFactory();
  ~CommandFactory();
  CommandFactory( CommandFactory const &src );
  CommandFactory &operator=( CommandFactory const &src );
  ACommand       *makeCommand( std::string commandName, std::string args, std::string nick );
};

#endif
