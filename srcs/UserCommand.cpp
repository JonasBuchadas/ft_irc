#include "UserCommand.hpp"

UserCommand::UserCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "USER", authenticator, args, fd ) {}

UserCommand::~UserCommand() {
}

UserCommand::UserCommand( UserCommand const &src ) : ACommand( src._authenticator ) {
  *this = src;
}

UserCommand &UserCommand::operator=( UserCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string UserCommand::execute() const {
  if ( _args.length() <= 1 )
    return "Invalid string\n\0";

  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_authenticator->isValidArg( str ) )
    return "Username contains invalid characters\n\0";

  if ( _authenticator->userNameExists( _userFD, str ) ) {
    return "Username already taken. Username not updated\n\0";
  }

  User *user = _authenticator->getUser( _userFD );
  if ( user == NULL ) {
    user = new User();
    user->setName( str );
    _authenticator->addUser( _userFD, user );
    return "Registered your username\n\0";
  }

  if ( user->getName().empty() ) {
    user->setName( str );
    return "Registered your username\n\0";
  }

  user->setName( str );
  return "Username successfully updated\n\0";
}
