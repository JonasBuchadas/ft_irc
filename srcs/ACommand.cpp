#include "ACommand.hpp"

ACommand::ACommand( Authenticator authenticator ) : _authenticator( authenticator ) {}

ACommand::ACommand( std::string name, Authenticator &authenticator, std::string args, int fd ) : _name( name ), _authenticator( authenticator ) {
  _args   = args;
  _userFD = fd;
}

ACommand::~ACommand() {
}

ACommand::ACommand( ACommand const &src ) : _authenticator( src._authenticator ) {
  *this = src;
}

ACommand &ACommand::operator=( ACommand const &src ) {
  if ( this == &src )
    return ( *this );
  _authenticator = src._authenticator;
  _args          = src._args;
  _userFD        = src._userFD;
  return ( *this );
}
