#include "commands/PartCommand.hpp"

PartCommand::PartCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "PART", userManager, channelManager, args, fd ) {}

PartCommand::~PartCommand() {
}

PartCommand::PartCommand( PartCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
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
  if ( !_userManager->isLoggedIn( _userFD ) )
    return serverResponse( ERR_NOTREGISTERED, "PART" );

  std::stringstream argsStream( _args );
  std::string       channelName;

  argsStream >> channelName;
  if ( !_channelManager->channelExists( channelName ) )
    return serverResponse( ERR_NOSUCHCHANNEL, "PART" );

  if ( !_channelManager->getChannel( channelName )->isUser( _userFD ) && !_channelManager->getChannel( channelName )->isOperator( _userFD ) )
    return serverResponse( ERR_USERNOTINCHANNEL, "PART" );

  if ( _channelManager->getChannel( channelName )->isUser( _userFD ) )
    _channelManager->getChannel( channelName )->removeUser( _userFD );
  if ( _channelManager->getChannel( channelName )->isOperator( _userFD ) )
    _channelManager->getChannel( channelName )->removeOperator( _userFD );
  pr.response = genUserMsg( _userManager->getUser( _userFD ), "PART" + _args );
  return pr;
}
