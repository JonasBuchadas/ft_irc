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

std::string PassCommand::execute() const {
  if ( _args.length() <= 1 )
    return "Invalid string\n\0";
  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_authenticator->isValidArg( str ) )
    return "Password contains invalid characters\n\0";

  User *user = _authenticator->getUser( _userFD );
  if ( user == NULL ) {
    user = new User();
    if ( str == _authenticator->getServerPass() )
      user->setPassword( true );
    _authenticator->addUser( _userFD, user );
  }
  if ( !user->getPassword() && str == _authenticator->getServerPass() )
    user->setPassword( true );

  return "Password registered\n\0";
}
