#include "commands/PassCommand.hpp"

PassCommand::PassCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "PASS", authenticator, args, fd ) {}

PassCommand::~PassCommand() {
}

PassCommand::PassCommand( PassCommand const &src ) : ACommand( src._authenticator ) {
  *this = src;
}

PassCommand &PassCommand::operator=( PassCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse PassCommand::execute() const {
  PreparedResponse pr = PreparedResponse();
  if ( _authenticator->getUser( _userFD ) && _authenticator->getUser( _userFD )->getLoggedIn() )
    pr.recipients.push_back( _userFD );
  if ( _args.length() <= 1 ) {
    pr.response = "Invalid string\n\0";
    return pr;
  }
  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_authenticator->isValidArg( str ) ) {
    pr.response = "Password contains invalid characters\n\0";
    return pr;
  }

  User *user = _authenticator->getUser( _userFD );
  if ( user == NULL ) {
    user = new User();
    if ( str == _authenticator->getServerPass() )
      user->setPassword( true );
    _authenticator->addUser( _userFD, user );
    pr.response = "Password registered\n\0";
    return pr;
  }

  if ( !user->getPassword() && str == _authenticator->getServerPass() ) {
    user->setPassword( true );
    pr.response = "Password registered\n\0";
  }
  if ( _authenticator->authenticateUser( _userFD ) ) {
    pr.response += "Successfully logged in!\n\0";
    pr.recipients.push_back( _userFD );
  }
  return pr;
}
