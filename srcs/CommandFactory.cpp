#include "CommandFactory.hpp"

CommandFactory::CommandFactory() {
}

CommandFactory::CommandFactory( const char *password ) {
  _authenticator  = new Authenticator( password );
  _channelManager = new ChannelManager();
}

CommandFactory::~CommandFactory() {
  delete _authenticator;
  delete _channelManager;
}

CommandFactory::CommandFactory( CommandFactory const &src ) {
  *this = src;
}

CommandFactory &CommandFactory::operator=( CommandFactory const &src ) {
  if ( this == &src )
    return ( *this );
  return ( *this );
}

ACommand *makeUserCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new UserCommand( authenticator, channelManager, args, fd );
}

ACommand *makePassCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new PassCommand( authenticator, channelManager, args, fd );
}

ACommand *makeNickCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new NickCommand( authenticator, channelManager, args, fd );
}

ACommand *makePrivCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new PrivCommand( authenticator, channelManager, args, fd );
}

ACommand *makeJoinCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new JoinCommand( authenticator, channelManager, args, fd );
}

ACommand *makeKickCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new KickCommand( authenticator, channelManager, args, fd );
}

ACommand *makeInviteCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new InviteCommand( authenticator, channelManager, args, fd );
}

ACommand *makePartCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new PartCommand( authenticator, channelManager, args, fd );
}

ACommand *makeNamesCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new NamesCommand( authenticator, channelManager, args, fd );
}

ACommand *makeModeCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new ModeCommand( authenticator, channelManager, args, fd );
}

ACommand *makeLogoutCommand( Authenticator *authenticator, ChannelManager *channelManager, std::string args, int fd ) {
  return new LogoutCommand( authenticator, channelManager, args, fd );
}

ACommand *CommandFactory::makeCommand( int fd, std::string commandName, std::string args, bool internal ) {
  const std::string enumInternalCommand[] = { "LOGOUT" };
  const funcPtr     enumInternalFunc[]    = { &makeLogoutCommand };
  const std::string enumCommand[]         = { "USER", "PASS", "NICK", "PRIVMSG", "JOIN", "KICK", "INVITE", "PART", "NAMES", "MODE" };
  const funcPtr     enumFunc[]            = {
      &makeUserCommand,
      &makePassCommand,
      &makeNickCommand,
      &makePrivCommand,
      &makeJoinCommand,
      &makeKickCommand,
      &makeInviteCommand,
      &makePartCommand,
      &makeNamesCommand,
      &makeModeCommand,
  };
  if ( internal ) {
    for ( int i = 0; i < (int)( sizeof( enumInternalCommand ) / sizeof( std::string ) ); i++ ) {
      if ( commandName == enumInternalCommand[i] ) {
        ACommand *c = ( enumInternalFunc[i]( _authenticator, _channelManager, args, fd ) );
        return c;
      }
    }
  }
  for ( int i = 0; i < (int)( sizeof( enumCommand ) / sizeof( std::string ) ); i++ ) {
    if ( commandName == enumCommand[i] ) {
      ACommand *c = ( enumFunc[i]( _authenticator, _channelManager, args, fd ) );
      return c;
    }
  }
  return new NoCommand( _authenticator, _channelManager, args, fd );
}
