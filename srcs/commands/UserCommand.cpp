#include "commands/UserCommand.hpp"

UserCommand::UserCommand( Authenticator *authenticator, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "USER", authenticator, channelManager, args, fd ) {}

UserCommand::~UserCommand() {
}

UserCommand::UserCommand( UserCommand const &src ) : ACommand( src._authenticator, src._channelManager ) {
  *this = src;
}

UserCommand &UserCommand::operator=( UserCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse UserCommand::execute() const {
  PreparedResponse pr = PreparedResponse();
  pr.recipients.push_back( _userFD );
  if ( _args.length() <= 1 ) {
    pr.response = "Invalid string\n\0";
    return pr;
  }
  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_authenticator->isValidArg( str ) ) {
    pr.response = "Username contains invalid characters\n\0";
    return pr;
  }

  User *user = _authenticator->getUser( _userFD );

  if (user && user->getLoggedIn())
  {
    pr.response = "User already authenticated.Nothing to do\n";
    return pr;
  }
  else if ( user == NULL ) {
    user = new User();
    user->setName( str );
    _authenticator->addUser( _userFD, user );
    pr.response = "Registered your username\n\0";
    return pr;
  }

  if ( _authenticator->userNameExists( _userFD, str ) ) {
    pr.response = "Username already taken. Username not updated\n\0";
    return pr;
  }


  if ( user->getName().empty() ) {
    user->setName( str );
    pr.response = "Registered your username\n\0";
    if ( _authenticator->authenticateUser( _userFD ) ) {
      pr.response += "Successfully logged in!\n\0";
    }
    return pr;
  }

  user->setName( str );
  pr.response = "Username successfully updated\n\0";
  return pr;
}
