#include "botcmds/NoCommand.hpp"

NoCommand::NoCommand( std::string args, std::string nick ) : ACommand( " ", args, nick ) {}

NoCommand::~NoCommand() {
}

NoCommand::NoCommand( NoCommand const &src ) : ACommand() {
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
