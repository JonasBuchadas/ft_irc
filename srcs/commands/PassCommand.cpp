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
  PreparedResponse pr = PreparedResponse();
  pr.recipients.push_back( _userFD );
  if ( _args.length() <= 1 ) {
    pr.response = "Invalid string\n\0";
    return pr;
  }
  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_userManager->isValidArg( str ) ) {
    pr.response = "Password contains invalid characters\n\0";
    return pr;
  }

  User *user = _userManager->getUser( _userFD );
  if ( user == NULL ) {
    user = new User();
    if ( str == _userManager->getServerPass() )
      user->setPassword( true );
    _userManager->addUser( _userFD, user );
    pr.response = "Password registered\n\0";
    return pr;
  } else if ( user->getLoggedIn() ) {
    pr.response = "User already authenticated.Nothing to do\n";
    return pr;
  }

  if ( !user->getPassword() && str == _userManager->getServerPass() ) {
    user->setPassword( true );
    pr.response = "Password registered\n\0";
  }
  if ( _userManager->authenticateUser( _userFD ) ) {
    pr.response += "Successfully logged in!\n\0";
  }
  return pr;
}
