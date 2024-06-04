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
  PreparedResponse pr = PreparedResponse();
  pr.recipients.push_back( _userFD );
  if ( _args.length() <= 1 ) {
    pr.response = genServerMsg(ERR_NEEDMOREPARAMS, "USER");
    return pr;
  }
  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_userManager->isValidArg( str ) ) {
    pr.response = genServerMsg(INVALIDAUTHELEM, "Username");
    return pr;
  }

  User *user = _userManager->getUser( _userFD );

  if ( user && user->getLoggedIn() ) {
    pr.response = genServerMsg(ERR_ALREADYREGISTERED, "");
    return pr;
  } else if ( user == NULL ) {
    user = new User();
    user->setName( str );
    _userManager->addUser( _userFD, user );
    pr.response = genServerMsg(UPD_AUTHELEM, "Username");
    return pr;
  }

  if ( _userManager->userNameExists( _userFD, str ) ) {
    pr.response = genServerMsg(ERR_USERNAMEINUSE, "");
    return pr;
  }

  if ( user->getName().empty() ) {
    user->setName( str );
    pr.response = genServerMsg(UPD_AUTHELEM, "Username");
    if ( _userManager->authenticateUser( _userFD ) ) {
      pr.response += genServerMsg(RPL_WELCOME, "");
    }
    return pr;
  }

  user->setName( str );
  pr.response = genServerMsg(UPD_AUTHELEM, "Username");
  return pr;
}
