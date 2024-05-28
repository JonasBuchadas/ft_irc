#include "ACommand.hpp"

ACommand::ACommand( BotManager *BotManager ) {
  _BotManager = BotManager;
}

ACommand::ACommand( std::string name, BotManager *BotManager, std::string args, std::string nick ) : _name( name ) {
  _BotManager = BotManager;
  _args       = args;
  _usernick   = nick;
}

ACommand::~ACommand() {
}

ACommand::ACommand( ACommand const &src ) : _BotManager( src._BotManager ) {
  *this = src;
}

ACommand &ACommand::operator=( ACommand const &src ) {
  if ( this == &src )
    return ( *this );
  _BotManager = src._BotManager;
  _args       = src._args;
  _usernick   = src._usernick;
  return ( *this );
}
