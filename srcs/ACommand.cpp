#include "ACommand.hpp"

ACommand::ACommand( UserManager *userManager, ChannelManager *channelManager ) {
  _userManager    = userManager;
  _channelManager = channelManager;
}

ACommand::ACommand( std::string name, UserManager *userManager,
                    ChannelManager *channelManager, std::string args, int fd ) : _name( name ) {
  _userManager    = userManager;
  _channelManager = channelManager;
  _args           = args;
  _userFD         = fd;
}

ACommand::~ACommand() {
}

ACommand::ACommand( ACommand const &src ) : _userManager( src._userManager ),
                                            _channelManager( src._channelManager ) {
  *this = src;
}

ACommand &ACommand::operator=( ACommand const &src ) {
  if ( this == &src )
    return ( *this );
  _userManager    = src._userManager;
  _channelManager = src._channelManager;
  _args           = src._args;
  _userFD         = src._userFD;
  return ( *this );
}

PreparedResponse ACommand::serverResponse( int code, const std::string &msg ) const {
  PreparedResponse preparedResponse;
  preparedResponse.allresponses[genServerMsg( code, _userManager->getNick( _userFD ) ,msg )].push_back( _userFD );
  return preparedResponse;
}
