#include "commands/NickCommand.hpp"

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

PreparedResponse NickCommand::execute() const {
  PreparedResponse pr = PreparedResponse();
  if ( _authenticator->getUser( _userFD ) && _authenticator->getUser( _userFD )->getLoggedIn() )
    pr.recipients.push_back( _userFD );
  if ( _args.length() <= 1 ) {
    pr.response = "Invalid string\n\0";
    return pr;
  }
  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_authenticator->isValidArg( str ) ) {
    pr.response = "Nickname contains invalid characters\n\0";
    return pr;
  }

  if ( _authenticator->nickNameExists( _userFD, str ) ) {
    pr.response = "Nickname already taken. Nickname not updated\n\0";
    return pr;
  }

  User *user = _authenticator->getUser( _userFD );
  if ( user == NULL ) {
    user = new User();
    user->setNick( str );
    _authenticator->addUser( _userFD, user );
    pr.response = "Registered your nickname\n\0";
    return pr;
  }

  if ( user->getNick().empty() ) {
    user->setNick( str );
    pr.response = "Registered your nickname\n\0";
    if ( _authenticator->authenticateUser( _userFD ) ) {
      pr.response += "Successfully logged in!\n\0";
      pr.recipients.push_back( _userFD );
    }
    return pr;
  }

  user->setNick( str );
  pr.response = "Nickname successfully updated\n\0";
  return pr;
}
