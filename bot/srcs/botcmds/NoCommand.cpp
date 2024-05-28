#include "botcmds/NoCommand.hpp"

NoCommand::NoCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( " ", BotManager, args, nick ) {}

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
