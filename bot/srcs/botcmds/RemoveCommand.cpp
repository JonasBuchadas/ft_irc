#include "botcmds/RemoveCommand.hpp"

RemoveCommand::RemoveCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "REMOVE", BotManager, args, nick ) {}

RemoveCommand::~RemoveCommand() {
}

RemoveCommand::RemoveCommand( RemoveCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

RemoveCommand &RemoveCommand::operator=( RemoveCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string RemoveCommand::execute() const {
  std::string channel;
  if (_args.find("#") != std::string::npos)
    channel = _args.substr(_args.find("#"));
  else
    return "Unknown channel name";

  Bot *bot = _BotManager->getBot( channel );
  if (bot->getUser( _usernick ) != "")
    bot->rmvUser( _usernick );
  else
    return "User not in userlist. Nothing to do!\n";
  return "Bot user removed\n";
}
