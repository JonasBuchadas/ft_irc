#include "commands/PrivCommand.hpp"

#include "Message.hpp"

PrivCommand::PrivCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "PRIVMSG", userManager, channelManager, args, fd ) {}

PrivCommand::~PrivCommand() {
}

PrivCommand::PrivCommand( PrivCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

PrivCommand &PrivCommand::operator=( PrivCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse PrivCommand::execute() const {
  PreparedResponse pr = PreparedResponse();
  if ( !_userManager->getUser( _userFD )->getLoggedIn() )
    return serverResponse( ERR_NOTREGISTERED, "PRIVMSG" );

  if ( _args.length() <= 1 )
    return serverResponse( ERR_NEEDMOREPARAMS, "PRIVMSG" );

  std::string target = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );
  if ( target.find( ":" ) != std::string::npos )
    target = target.substr( 0, target.find( ":" ) );
  if ( (target.find("#") == std::string::npos && _userManager->getFdFromNick( target ) == -1) \
  || ( target.find("#") != std::string::npos && !_channelManager->channelExists( target ) ) )
    return serverResponse( ERR_NOSUCHNICK, target );

  unsigned int long pos = _args.find( ":" );
  if ( pos == std::string::npos )
    return serverResponse( ERR_NOTEXTTOSEND, "" );

  std::string send = _args.substr( pos + 1 );
  pos              = _args.find( "DCC SEND" );
  if ( pos != std::string::npos ) {
    send = send.substr( send.find("DCC SEND") + 9 );
    std::istringstream iss( send );
    std::string        filename, portStr, filesizeStr;
    uint32_t ip;
    iss >> filename;
    iss >> ip;
    iss >> portStr >> filesizeStr;
    struct sockaddr_in addr;
    socklen_t          userlen = sizeof( addr );
    if ( getpeername( _userFD, (struct sockaddr *)&addr, &userlen ) == -1 )
      return serverResponse( ERR_USERNOTFOUND, "" );
    if ( ip != _userManager->getUser( _userFD )->getIp() )
      return serverResponse( ERR_IPNOTFOUND, "" );
  }
  if ( target.find( "#" ) == std::string::npos && _userManager->getUser(_userManager->getFdFromNick( target ))->getLoggedIn() )
    pr.allresponses[genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG" + _args )].push_back( _userManager->getFdFromNick( target ) );
  else if (target.find( "#" ) != std::string::npos && (_channelManager->getChannel( target )->isUser( _userFD ) \
  || _channelManager->getChannel( target )->isOperator( _userFD ))) {
    pr.allresponses[genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG" + _args )] \
    = _channelManager->getChannel( target )->getAllMembersSansUser( _userFD );
  }
  else if ( target.find( "#" ) != std::string::npos )
    return serverResponse( ERR_USERNOTINCHANNEL, target );
  else
    return serverResponse( ERR_TARGETNOTAUTH, target );
  return pr;
}
