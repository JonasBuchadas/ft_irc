#include "commands/NoCommand.hpp"

NoCommand::NoCommand( UserManager *userManager, ChannelManager *channelManager,
                      std::string args, int fd ) : ACommand( "NO", userManager, channelManager, args, fd ) {}

NoCommand::~NoCommand() {
}

NoCommand::NoCommand( NoCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
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
