#include "commands/NoCommand.hpp"

NoCommand::NoCommand( BotManager *BotManager, std::string args, int fd ) : ACommand( " ", BotManager, args, fd ) {}

NoCommand::~NoCommand() {
}

NoCommand::NoCommand( NoCommand const &src ) : ACommand( src._BotManager ) {
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
