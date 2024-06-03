#include "commands/KickCommand.hpp"

KickCommand::KickCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "KICK", userManager, channelManager, args, fd ) {}

KickCommand::~KickCommand() {
}

KickCommand::KickCommand( KickCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
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
