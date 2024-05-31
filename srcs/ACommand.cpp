#include "ACommand.hpp"

ACommand::ACommand( Authenticator *authenticator, ChannelManager *channelManager ) {
  _authenticator  = authenticator;
  _channelManager = channelManager;
}

ACommand::ACommand( std::string name, Authenticator *authenticator,
                    ChannelManager *channelManager, std::string args, int fd ) : _name( name ) {
  _authenticator  = authenticator;
  _channelManager = channelManager;
  _args           = args;
  _userFD         = fd;
}

ACommand::~ACommand() {
}

ACommand::ACommand( ACommand const &src ) : _authenticator( src._authenticator ),
                                            _channelManager( src._channelManager ) {
  *this = src;
}

ACommand &ACommand::operator=( ACommand const &src ) {
  if ( this == &src )
    return ( *this );
  _authenticator  = src._authenticator;
  _channelManager = src._channelManager;
  _args           = src._args;
  _userFD         = src._userFD;
  return ( *this );
}
