#include "commands/JoinCommand.hpp"

JoinCommand::JoinCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "JOIN", authenticator, args, fd ) {}

JoinCommand::~JoinCommand() {
}

JoinCommand::JoinCommand( JoinCommand const &src ) : ACommand( src._authenticator ) {
  *this = src;
}

JoinCommand &JoinCommand::operator=( JoinCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse JoinCommand::execute() const {
  // TODO: Implement me!!!
}
