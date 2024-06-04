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
  if ( !_userManager->getUser( _userFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_NOTREGISTERED, "PRIVMSG");
    return pr;
  }
  if ( _args.length() <= 1 ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_NEEDMOREPARAMS, "PRIVMSG");
    return pr;
  }
  std::string target = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );
  if ( target.find( ":" ) != std::string::npos )
    target = target.substr( 0, target.find( ":" ) );
  if ( _userManager->getFdFromNick( target ) == -1 && !_channelManager->channelExists( target ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg( ERR_NOSUCHNICK, "PRIVMSG" );
    return pr;
  }

  unsigned int long pos = _args.find( ":" );
  if ( pos == std::string::npos ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_NOTEXTTOSEND, "");
    return pr;
  }
  std::string send = _args.substr( pos + 1 );
  pos              = _args.find( "DCC SEND" );
  if ( pos == std::string::npos ) {
    if ( target.find( "#" ) == std::string::npos )
      pr.recipients.push_back( _userManager->getFdFromNick( target ) );
    else {
      std::vector<int> users = _channelManager->getChannel( target )->getAllUsers();
      pr.recipients.clear();
      for ( int i = 0; i < (int)users.size(); i++ ) {
        if ( users[i] != _userFD )
          pr.recipients.push_back( users[i] );
      }
    }
    pr.response = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG" + _args );
    return pr;
  } else {
    send = send.substr( pos + 8 );
    std::istringstream iss( send );
    std::string        filename, ipStr, portStr, filesizeStr;
    iss >> filename >> ipStr >> portStr >> filesizeStr;
    struct sockaddr_in addr;
    socklen_t          userlen = sizeof( addr );
    if ( getpeername( _userManager->getFdFromNick( target ), (struct sockaddr *)&addr, &userlen ) == -1 ) {
      pr.recipients.push_back( _userFD );
      pr.response = "Couldn't find user\n";  // Change later
      return pr;
    }
    if ( ntohl( addr.sin_addr.s_addr ) != _userManager->getUser( _userManager->getFdFromNick( target ) )->getIp() ) {
      pr.recipients.push_back( _userFD );
      pr.response = "Invalid ip address\n";  // Change later
      return pr;
    }
    pr.recipients.push_back( _userFD );
    pr.response = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG" + _args );
    return pr;
  }
  return pr;
}
