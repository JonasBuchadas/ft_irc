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
  PreparedResponse pr = PreparedResponse();

  if ( !_userManager->isLoggedIn( _userFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = "Not logged in\n";
    return pr;
  }

  std::stringstream ss( _args );
  std::string       kickedNick;
  std::string       channelName;
  std::string       invalidArg;
  ss >> kickedNick;
  ss >> channelName;
  ss >> invalidArg;

  if ( kickedNick.empty() || channelName.empty() || !invalidArg.empty() ) {
    pr.recipients.push_back( _userFD );
    pr.response = "Invalid args\n";
    return pr;
  }

  if ( !_userManager->nickNameExists( _userFD, kickedNick ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = "Target nick does not exist\n";
    return pr;
  }

  int kickedFD = _userManager->getFdFromNick( kickedNick );
  if ( !_userManager->isLoggedIn( kickedFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = "Target nick is not logged in\n";
    return pr;
  }

  if ( !_channelManager->channelExists( channelName ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = "Channel does not exist\n";
    return pr;
  }

  if ( !_channelManager->getChannel( channelName )->isUser( _userFD ) &&
       !_channelManager->getChannel( channelName )->isOperator( _userFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = "Not an user or operator of channel\n";
    return pr;
  }

  if ( !_channelManager->getChannel( channelName )->isUser( kickedFD ) &&
       !_channelManager->getChannel( channelName )->isOperator( kickedFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = "Target nick not an user or operator of channel\n";
    return pr;
  }

  _channelManager->getChannel( channelName )->removeUser( kickedFD );
  _channelManager->getChannel( channelName )->removeOperator( kickedFD );

  pr.recipients.push_back( kickedFD );
  pr.response = genUserMsg( _userManager->getUser( _userFD ), "KICK" + _args );
  return pr;
}
