#include "botcmds/InvalidCommand.hpp"

InvalidCommand::InvalidCommand( std::string args, std::string nick ) : ACommand( "INVALID", args, nick ) {}

InvalidCommand::~InvalidCommand() {
}

InvalidCommand::InvalidCommand( InvalidCommand const &src ) : ACommand() {
  *this = src;
}

InvalidCommand &InvalidCommand::operator=( InvalidCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string InvalidCommand::execute() const {
  return "Unknown command\n";
}
