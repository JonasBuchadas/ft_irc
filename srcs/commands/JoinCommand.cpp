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

  std::stringstream ss( _args );
  std::string       channelName;
  std::string       password;
  std::string       invalidArg;
  ss >> channelName;
  ss >> password;
  ss >> invalidArg;

  if ( channelName.empty() || !invalidArg.empty() ) {
    pr.response = "Invalid args\n";
    return pr;
  }

  if ( channelName[0] != '#' ) {
    pr.response = "Invalid channel name\n";
    return pr;
  }

  if ( !_channelManager->channelExists( channelName ) ) {
    Channel *channel = new Channel( channelName );
    _channelManager->addChannel( channelName, channel );
    _channelManager->getChannel( channelName )->addOperator( _userFD );
    pr.response = genUserMsg( _userManager->getUser( _userFD ), "JOIN" + _args );
    return pr;
  }

  if ( _channelManager->getChannel( channelName )->isInviteOnly() && !_channelManager->getChannel( channelName )->isInvitee( _userFD ) ) {
    pr.response = "Channel is invite-only\n";
    return pr;
  }

  if ( password != _channelManager->getChannel( channelName )->getPassword() ) {
    pr.response = "Wrong channel password\n";
    return pr;
  }

  if ( _channelManager->getChannel( channelName )->isUser( _userFD ) || _channelManager->getChannel( channelName )->isOperator( _userFD ) ) {
    pr.response = "Already in the channel\n";
    return pr;
  }
  _channelManager->getChannel( channelName )->addUser( _userFD );

  pr.response = genUserMsg( _userManager->getUser( _userFD ), "JOIN" + _args );
  return pr;
}
