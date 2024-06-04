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
    pr.response = genServerMsg(ERR_NEEDMOREPARAMS, "PASS");
    return pr;
  }
  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_userManager->isValidArg( str ) ) {
    pr.response = genServerMsg(INVALIDAUTHELEM, "Password");
    return pr;
  }

  User *user = _userManager->getUser( _userFD );
  if ( user == NULL ) {
    user = new User();
    if ( str == _userManager->getServerPass() )
      user->setPassword( true );
    _userManager->addUser( _userFD, user );
    pr.response = genServerMsg(UPD_AUTHELEM, "Password");
    return pr;
  } else if ( user->getLoggedIn() ) {
    pr.response = genServerMsg(ERR_ALREADYREGISTERED, "");
    return pr;
  }

  if ( !user->getPassword() && str == _userManager->getServerPass() ) {
    user->setPassword( true );
    pr.response = genServerMsg(UPD_AUTHELEM, "Password");
  }
  if ( _userManager->authenticateUser( _userFD ) ) {
    pr.response += genServerMsg(RPL_WELCOME, "");
  }
  return pr;
}
