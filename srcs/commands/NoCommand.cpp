#include "commands/NoCommand.hpp"

NoCommand::NoCommand( Authenticator *authenticator, ChannelManager *channelManager,
                      std::string args, int fd ) : ACommand( "NO", authenticator, channelManager, args, fd ) {}

NoCommand::~NoCommand() {
}

NoCommand::NoCommand( NoCommand const &src ) : ACommand( src._authenticator, src._channelManager ) {
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
