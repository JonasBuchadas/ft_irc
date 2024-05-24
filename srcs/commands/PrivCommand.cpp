#include "commands/PrivCommand.hpp"
#include "Message.hpp"

PrivCommand::PrivCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "PRIVMSG", authenticator, args, fd ) {}

PrivCommand::~PrivCommand() {
}

PrivCommand::PrivCommand( PrivCommand const &src ) : ACommand( src._authenticator ) {
  *this = src;
}

PrivCommand &PrivCommand::operator=( PrivCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string PrivCommand::execute() const {
  if (!_authenticator->getUser( _userFD ))
    return genServerMsg( 451, "PRIVMSG" );
  if ( _args.length() <= 1 )
    return "Invalid string\n";
  std::string target = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );
  if (target.find(":") != std::string::npos)
    target = target.substr(0, target.find(":"));

  if (_authenticator->getFdFromNick( target ) == -1)
    return genServerMsg( 401, "PRIVMSG" );

  unsigned int long pos = _args.find(":");
  if (pos == std::string::npos)
    return "error1\n";   // Change later
  std::string send = _args.substr( pos + 1 );
  pos = _args.find("DCC SEND");
  if (pos == std::string::npos )
    return genUserMsg( _authenticator->getUser( _userFD), "PRIVMSG" + _args );
  else
  {
    send = send.substr(pos + 8);
    std::istringstream iss(send);
    std::string filename, ipStr, portStr, filesizeStr;
    iss >> filename >> ipStr >> portStr >> filesizeStr;
    struct sockaddr_in addr;
    socklen_t          userlen = sizeof(addr);
    if (getpeername( _authenticator->getFdFromNick( target ), (struct sockaddr *)&addr, &userlen ) == -1)
      return "error2\n";   // Change later
    if (ntohl(addr.sin_addr.s_addr) != _authenticator->getUser( _authenticator->getFdFromNick( target ) )->getIp())
      return "error2\n";   // Change later
    return genUserMsg( _authenticator->getUser( _userFD), "PRIVMSG" + _args );
  }

  return "";
}
