#include "commands/PassCommand.hpp"

PassCommand::PassCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "PASS", userManager, channelManager, args, fd ) {}

PassCommand::~PassCommand() {
}

PassCommand::PassCommand( PassCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

PassCommand &PassCommand::operator=( PassCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse PassCommand::execute() const {
  if ( _args.length() <= 1 )
    return serverResponse( ERR_NEEDMOREPARAMS, "PASS" );

  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_userManager->isValidArg( str ) )
    return serverResponse( INVALIDAUTHELEM, "Password" );

  User *user = _userManager->getUser( _userFD );
  if ( user == NULL ) {
    user = new User();
    if ( str == _userManager->getServerPass() )
      user->setPassword( true );
    _userManager->addUser( _userFD, user );
    return serverResponse( UPD_AUTHELEM, "Password" );
  } else if ( user->getLoggedIn() )
    return serverResponse( ERR_ALREADYREGISTERED, "" );

  PreparedResponse pr;
  if ( !user->getPassword() && str == _userManager->getServerPass() ) {
    user->setPassword( true );
    pr = serverResponse( UPD_AUTHELEM, "Password" );
  }
  if ( _userManager->authenticateUser( _userFD ) ) {
    pr.response += genServerMsg( RPL_WELCOME, _userManager->getNick( _userFD ), "" );
  }
  return pr;
}
