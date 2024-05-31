#include "commands/PartCommand.hpp"

PartCommand::PartCommand( Authenticator *authenticator, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "PART", authenticator, channelManager, args, fd ) {}

PartCommand::~PartCommand() {
}

PartCommand::PartCommand( PartCommand const &src ) : ACommand( src._authenticator, src._channelManager ) {
  *this = src;
}

PartCommand &PartCommand::operator=( PartCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse PartCommand::execute() const {
  // TODO: Implement me!
  return PreparedResponse();
}
