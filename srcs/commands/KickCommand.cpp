#include "commands/KickCommand.hpp"

KickCommand::KickCommand( Authenticator *authenticator, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "KICK", authenticator, channelManager, args, fd ) {}

KickCommand::~KickCommand() {
}

KickCommand::KickCommand( KickCommand const &src ) : ACommand( src._authenticator, src._channelManager ) {
  *this = src;
}

KickCommand &KickCommand::operator=( KickCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse KickCommand::execute() const {
  // TODO: Implement me;
  return PreparedResponse();
}
