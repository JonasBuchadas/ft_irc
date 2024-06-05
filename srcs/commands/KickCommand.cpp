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
  if ( !_userManager->isLoggedIn( _userFD ) )
    return serverResponse( ERR_NOTREGISTERED, "KICK" );

  std::stringstream argsStream( _args );
  std::string       kickedNick, channelName, invalidArg;
  argsStream >> channelName >> kickedNick >> invalidArg;

  if ( kickedNick.empty() || channelName.empty() || !invalidArg.empty() )
    return serverResponse( ERR_NEEDMOREPARAMS, "KICK" );

  if ( !_userManager->nickNameExists( kickedNick ))
    return serverResponse( ERR_NOSUCHNICK, "KICK" );

  int kickedFD = _userManager->getFdFromNick( kickedNick );
  if ( !_userManager->isLoggedIn( kickedFD ) )
    return serverResponse( ERR_TARGETNOTAUTH, "" );

  if ( !_channelManager->channelExists( channelName ) )
    return serverResponse( ERR_NOSUCHCHANNEL, "KICK" );

  if ( !_channelManager->getChannel( channelName )->isUser( _userFD ) &&
       !_channelManager->getChannel( channelName )->isOperator( _userFD ) )
    return serverResponse( ERR_USERNOTINCHANNEL, "KICK" );

  if ( !_channelManager->getChannel( channelName )->isUser( kickedFD ) &&
       !_channelManager->getChannel( channelName )->isOperator( kickedFD ) )
    return serverResponse( ERR_TARGETNOTINCHANNEL, "" );

  _channelManager->getChannel( channelName )->removeUser( kickedFD );
  _channelManager->getChannel( channelName )->removeOperator( kickedFD );

  PreparedResponse pr = PreparedResponse();
  pr.recipients.push_back( kickedFD );
  pr.response = genUserMsg( _userManager->getUser( _userFD ), "KICK " + kickedNick );
  return pr;
}
