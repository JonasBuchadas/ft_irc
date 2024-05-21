#include "JoinCommand.hpp"

JoinCommand::JoinCommand() : ACommand() {}

JoinCommand::~JoinCommand() {
}

JoinCommand::JoinCommand( JoinCommand const &src ) : ACommand() {
  *this = src;
}

JoinCommand &JoinCommand::operator=( JoinCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

void JoinCommand::execute() const {
  // TODO: Implement me!!!
}
