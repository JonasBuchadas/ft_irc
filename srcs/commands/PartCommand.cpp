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
  PreparedResponse pr = PreparedResponse();
  pr.recipients.push_back( _userFD );
  if ( !_authenticator->isLoggedIn( _userFD ) ) {
    pr.response = "Not logged in\n";
    return pr;
  }
  std::stringstream ss( _args );
  std::string       channelName;

  ss >> channelName;
  if ( !_channelManager->channelExists( channelName ) ) {
    pr.response = "Channel does not exist\n";
    return pr;
  }
  if ( !_channelManager->getChannel( channelName )->isUser( _userFD ) && !_channelManager->getChannel( channelName )->isOperator( _userFD ) ) {
    pr.response = "Already not in the channel\n";
    return pr;
  }
  if ( _channelManager->getChannel( channelName )->isUser( _userFD ) )
    _channelManager->getChannel( channelName )->removeUser( _userFD );
  if ( _channelManager->getChannel( channelName )->isOperator( _userFD ) )
    _channelManager->getChannel( channelName )->removeOperator( _userFD );
  pr.response = genUserMsg( _authenticator->getUser( _userFD ), "PART" + _args );
  return pr;
}
