#include "botcmds/AcceptCommand.hpp"

AcceptCommand::AcceptCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "ACCEPT", BotManager, args, nick ) {}

AcceptCommand::~AcceptCommand() {
}

AcceptCommand::AcceptCommand( AcceptCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

AcceptCommand &AcceptCommand::operator=( AcceptCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string AcceptCommand::execute() const {
  std::string channel;
  if (_args.find("#") != std::string::npos)
    channel = _args.substr(_args.find("#"));
  else
    return "Unknown channel name";

  Bot *bot = _BotManager->getBot( channel );
  if (bot->getUser( _usernick ) != "")
    return "User already accepted. Nothing to do!\n";
  else
    bot->addUser( _usernick );
  return "User accepted!\n";
}
