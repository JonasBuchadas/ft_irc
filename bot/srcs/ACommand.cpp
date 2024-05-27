#include "ACommand.hpp"

ACommand::ACommand( BotManager *BotManager ) {
  _BotManager = BotManager;
}

ACommand::ACommand( std::string name, BotManager *BotManager, std::string args, int fd ) : _name( name ) {
  _BotManager = BotManager;
  _args          = args;
  _userFD        = fd;
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
  _args          = src._args;
  _userFD        = src._userFD;
  return ( *this );
}
