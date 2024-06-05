#include "commands/UserCommand.hpp"

UserCommand::UserCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "USER", userManager, channelManager, args, fd ) {}

UserCommand::~UserCommand() {
}

UserCommand::UserCommand( UserCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

UserCommand &UserCommand::operator=( UserCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse UserCommand::execute() const {
  if ( _args.length() <= 1 )
    return serverResponse( ERR_NEEDMOREPARAMS, "USER" );

  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_userManager->isValidArg( str ) )
    return serverResponse( INVALIDAUTHELEM, "Username" );

  User *user = _userManager->getUser( _userFD );

  if ( user && user->getLoggedIn() ) {
    return serverResponse( ERR_ALREADYREGISTERED, "" );
  } else if ( user == NULL ) {
    user = new User();
    user->setName( str );
    _userManager->addUser( _userFD, user );
    return serverResponse( UPD_AUTHELEM, "Username" );
  }
  if ( _userManager->userNameExists( _userFD, str ) )
    return serverResponse( ERR_USERNAMEINUSE, "" );

  user->setName( str );
  PreparedResponse pr = serverResponse( UPD_AUTHELEM, "Username" );
  if ( _userManager->authenticateUser( _userFD ) ) {
    pr.response += genServerMsg( RPL_WELCOME, "" );
  }
  return pr;
}
