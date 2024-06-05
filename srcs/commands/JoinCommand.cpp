#include "commands/JoinCommand.hpp"

JoinCommand::JoinCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "JOIN", userManager, channelManager, args, fd ) {}

JoinCommand::~JoinCommand() {
}

JoinCommand::JoinCommand( JoinCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
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
  if ( !_userManager->isLoggedIn( _userFD ) )
    return serverResponse( ERR_NOTREGISTERED, "JOIN" );

  std::stringstream argsStream( _args );
  std::string       channelName, password, invalidArg;
  argsStream >> channelName >> password >> invalidArg;

  if ( channelName.empty() || !invalidArg.empty() )
    return serverResponse( ERR_NEEDMOREPARAMS, "JOIN" );

  if ( channelName[0] != '#' )
    return serverResponse( ERR_NOSUCHCHANNEL, "JOIN" );

  if ( !_channelManager->channelExists( channelName ) ) {
    Channel *channel = new Channel( channelName );
    _channelManager->addChannel( channelName, channel );
    _channelManager->getChannel( channelName )->addOperator( _userFD );
    if ( !password.empty() )
      _channelManager->getChannel( channelName )->setPassword( password );
    pr.response = genUserMsg( _userManager->getUser( _userFD ), "JOIN " + channelName );
    return pr;
  }

  if ( _channelManager->getChannel( channelName )->isInviteOnly() && !_channelManager->getChannel( channelName )->isInvitee( _userFD ) )
    return serverResponse( ERR_INVITEONLYCHAN, channelName );

  if ( password != _channelManager->getChannel( channelName )->getPassword() )
    return serverResponse( ERR_PASSWDMISMATCH, "" );

  if ( _channelManager->getChannel( channelName )->isUser( _userFD ) || _channelManager->getChannel( channelName )->isOperator( _userFD ) )
    return serverResponse( ERR_USERONCHANNEL, _userManager->getNick( _userFD ) );

  _channelManager->getChannel( channelName )->addUser( _userFD );
  if (_channelManager->getChannel( channelName )->isInvitee( _userFD ))
    _channelManager->getChannel( channelName )->removeInvitee( _userFD );
  pr.response = genUserMsg( _userManager->getUser( _userFD ), "JOIN " + channelName );
  return pr;
}
