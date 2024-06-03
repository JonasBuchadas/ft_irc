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
  if ( !_userManager->isLoggedIn( _userFD ) ) {
    pr.response = "Not logged in\n";
    return pr;
  }
  int i = 0;
  while ( _args[i] && _args[i] == ' ' )
    i++;
  if ( _args.length() > 1 && _args[i] != '#' ) {
    pr.response = "Invalid channel name\n";
    return pr;
  }
  std::string channelName = _args.substr( i );
  if ( !_channelManager->channelExists( channelName ) ) {
    Channel *channel = new Channel( channelName );
    _channelManager->addChannel( channelName, channel );
    _channelManager->getChannel( channelName )->addOperator( _userFD );
  } else {
    _channelManager->getChannel( channelName )->addUser( _userFD );
  }
  pr.response = genUserMsg( _userManager->getUser( _userFD ), "JOIN" + _args );
  return pr;
}
