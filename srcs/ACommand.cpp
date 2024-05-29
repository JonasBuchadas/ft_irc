#include "ACommand.hpp"

ACommand::ACommand( Authenticator *authenticator, ChannelManager *channelmanager ) {
  _authenticator = authenticator;
  _channelmanager = channelmanager;
}

ACommand::ACommand( std::string name, Authenticator *authenticator, \
ChannelManager *channelmanager, std::string args, int fd ) : _name( name ) {
  _authenticator  = authenticator;
  _channelmanager = channelmanager;
  _args           = args;
  _userFD         = fd;
}

ACommand::~ACommand() {
}

ACommand::ACommand( ACommand const &src ) : _authenticator( src._authenticator ), \
_channelmanager( src._channelmanager ) {
  *this = src;
}

ACommand &ACommand::operator=( ACommand const &src ) {
  if ( this == &src )
    return ( *this );
  _authenticator  = src._authenticator;
  _channelmanager = src._channelmanager;
  _args           = src._args;
  _userFD         = src._userFD;
  return ( *this );
}
