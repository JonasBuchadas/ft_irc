#include "commands/NickCommand.hpp"

NickCommand::NickCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "NICK", userManager, channelManager, args, fd ) {}

NickCommand::~NickCommand() {
}

NickCommand::NickCommand( NickCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

NickCommand &NickCommand::operator=( NickCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse NickCommand::execute() const {
  if ( _args.length() <= 1 )
    return serverResponse( ERR_NEEDMOREPARAMS, "NICK" );

  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_userManager->isValidArg( str ) )
    return serverResponse( ERR_ERRONEUSNICKNAME, "" );

  User *user = _userManager->getUser( _userFD );
  
  if ( _userManager->nickNameExists( str ) && (user == NULL || str != _userManager->getNick( _userFD )))
    return serverResponse( ERR_NICKNAMEINUSE, "" );

  if ( user == NULL ) {
    user = new User();
    user->setNick( str );
    _userManager->addUser( _userFD, user );
    return serverResponse( UPD_AUTHELEM, "Nickname" );
  }
  user->setNick( str );
  PreparedResponse pr = serverResponse( UPD_AUTHELEM, "Nickname" );
  if ( _userManager->authenticateUser( _userFD ) ) {
    _userManager->setUserIp( _userFD );
    pr.allresponses[genServerMsg( RPL_WELCOME, _userManager->getNick( _userFD ), _userManager->getNick( _userFD ) )].push_back( _userFD );
  }
  return pr;
}
