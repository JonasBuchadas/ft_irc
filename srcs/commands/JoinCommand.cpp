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
  if ( !_authenticator->authenticateUser( _userFD ) ) {
    pr.response = "Not logged in";
  }
  if ( !_channelManager->channelExists( _args ) ) {
    Channel *channel = new Channel( _args );
    _channelManager->addChannel( channel->getName(), channel );
  }
  _channelManager->getChannel( _args )->addUser( _userFD );
  pr.response = genUserMsg( _authenticator->getUser( _userFD ), "JOIN" + _args );
  return pr;
}
