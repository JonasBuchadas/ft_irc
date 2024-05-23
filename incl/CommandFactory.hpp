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

typedef ACommand *( *funcPtr )( Authenticator *authenticator, std::string _args, int fd );

class CommandFactory {
 private:
 public:
  CommandFactory();
  ~CommandFactory();
  CommandFactory( CommandFactory const &src );
  CommandFactory &operator=( CommandFactory const &src );
  ACommand       *makeCommand( std::string commandName, Authenticator *authenticator, std::string args, int fd );
};

#endif
