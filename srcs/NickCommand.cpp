#include "NickCommand.hpp"

NickCommand::NickCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "NICK", authenticator, args, fd ) {}

NickCommand::~NickCommand() {
}

NickCommand::NickCommand( NickCommand const &src ) : ACommand( src._authenticator ) {
  *this = src;
}

NickCommand &NickCommand::operator=( NickCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string NickCommand::execute() const {
  if ( _args.length() <= 1 )
    return "Invalid string\n\0";
  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_authenticator->isValidArg( str ) )
    return "Nickname contains invalid characters\n\0";

  if ( _authenticator->nickNameExists( _userFD, str ) ) {
    return "Nickname already taken. Nickname not updated\n\0";
  }

  User *user = _authenticator->getUser( _userFD );
  if ( user == NULL ) {
    user = new User();
    user->setNick( str );
    _authenticator->addUser( _userFD, user );
    return "Registered your nickname\n\0";
  }

  if ( user->getNick().empty() ) {
    user->setNick( str );
    return "Registered your nickname\n\0";
  }

  user->setNick( str );
  return "Nickname successfully updated\n\0";
}
