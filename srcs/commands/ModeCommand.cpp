#include "commands/ModeCommand.hpp"

ModeCommand::ModeCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "MODE", userManager, channelManager, args, fd ) {}

ModeCommand::~ModeCommand() {
}

ModeCommand::ModeCommand( ModeCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

ModeCommand &ModeCommand::operator=( ModeCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse ModeCommand::execute() const {
  // TODO: Implement me!
  return PreparedResponse();
}
