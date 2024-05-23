#include "NoCommand.hpp"

NoCommand::NoCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "PASS", authenticator, args, fd ) {}

NoCommand::~NoCommand() {
}

NoCommand::NoCommand( NoCommand const &src ) : ACommand( src._authenticator ) {
  *this = src;
}

NoCommand &NoCommand::operator=( NoCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string NoCommand::execute() const {
  return "";
}
