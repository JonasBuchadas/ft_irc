#include "commands/JoinCommand.hpp"

JoinCommand::JoinCommand( Authenticator *authenticator, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "JOIN", authenticator, channelManager, args, fd ) {}

JoinCommand::~JoinCommand() {
}

JoinCommand::JoinCommand( JoinCommand const &src ) : ACommand( src._authenticator, src._channelManager ) {
  *this = src;
}

JoinCommand &JoinCommand::operator=( JoinCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse JoinCommand::execute() const {
  PreparedResponse pr = PreparedResponse();
  pr.recipients.push_back( _userFD );
  pr.response = "Joining!\n";
  return pr;
}
