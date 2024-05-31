#include "commands/InviteCommand.hpp"

InviteCommand::InviteCommand( Authenticator *authenticator, ChannelManager *channelManager,
                              std::string args, int fd ) : ACommand( "INVITE", authenticator, channelManager, args, fd ) {}

InviteCommand::~InviteCommand() {
}

InviteCommand::InviteCommand( InviteCommand const &src ) : ACommand( src._authenticator, src._channelManager ) {
  *this = src;
}

InviteCommand &InviteCommand::operator=( InviteCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse InviteCommand::execute() const {
  // TODO: Implement me!
  return PreparedResponse();
}
