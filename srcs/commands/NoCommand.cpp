#include "commands/NoCommand.hpp"

NoCommand::NoCommand( Authenticator *authenticator, ChannelManager *channelmanager, \
std::string args, int fd ) : ACommand( "NO", authenticator, channelmanager, args, fd ) {}

NoCommand::~NoCommand() {
}

NoCommand::NoCommand( NoCommand const &src ) : ACommand( src._authenticator, src._channelmanager ) {
  *this = src;
}

NoCommand &NoCommand::operator=( NoCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse NoCommand::execute() const {
  return PreparedResponse();
}
