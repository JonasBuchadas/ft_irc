#include "ACommand.hpp"

ACommand::ACommand() {}

ACommand::ACommand( std::string name, std::string args, std::string nick ) : _name( name ) {
  _args       = args;
  _usernick   = nick;
}

ACommand::~ACommand() {
}

ACommand::ACommand( ACommand const &src ) {
  *this = src;
}

ACommand &ACommand::operator=( ACommand const &src ) {
  if ( this == &src )
    return ( *this );
  _args       = src._args;
  _usernick   = src._usernick;
  return ( *this );
}
