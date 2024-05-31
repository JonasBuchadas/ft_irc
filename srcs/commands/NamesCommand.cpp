#include "commands/NamesCommand.hpp"

NamesCommand::NamesCommand( Authenticator *authenticator, ChannelManager *channelManager,
                            std::string args, int fd ) : ACommand( "NAMES", authenticator, channelManager, args, fd ) {}

NamesCommand::~NamesCommand() {
}

NamesCommand::NamesCommand( NamesCommand const &src ) : ACommand( src._authenticator, src._channelManager ) {
  *this = src;
}

NamesCommand &NamesCommand::operator=( NamesCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse NamesCommand::execute() const {
  // TODO: Implement me!
  return PreparedResponse();
}
