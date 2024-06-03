#include "CommandFactory.hpp"

CommandFactory::CommandFactory() {
}

CommandFactory::CommandFactory( const char *password ) {
  _userManager    = new UserManager( password );
  _channelManager = new ChannelManager();
}

CommandFactory::~CommandFactory() {
  delete _userManager;
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

ACommand *makeUserCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new UserCommand( userManager, channelManager, args, fd );
}

ACommand *makePassCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new PassCommand( userManager, channelManager, args, fd );
}

ACommand *makeNickCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new NickCommand( userManager, channelManager, args, fd );
}

ACommand *makePrivCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new PrivCommand( userManager, channelManager, args, fd );
}

ACommand *makeJoinCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new JoinCommand( userManager, channelManager, args, fd );
}

ACommand *makeKickCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new KickCommand( userManager, channelManager, args, fd );
}

ACommand *makeInviteCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new InviteCommand( userManager, channelManager, args, fd );
}

ACommand *makePartCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new PartCommand( userManager, channelManager, args, fd );
}

ACommand *makeNamesCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new NamesCommand( userManager, channelManager, args, fd );
}

ACommand *makeModeCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new ModeCommand( userManager, channelManager, args, fd );
}

ACommand *makeLogoutCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd ) {
  return new LogoutCommand( userManager, channelManager, args, fd );
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
        ACommand *c = ( enumInternalFunc[i]( _userManager, _channelManager, args, fd ) );
        return c;
      }
    }
  }
  for ( int i = 0; i < (int)( sizeof( enumCommand ) / sizeof( std::string ) ); i++ ) {
    if ( commandName == enumCommand[i] ) {
      ACommand *c = ( enumFunc[i]( _userManager, _channelManager, args, fd ) );
      return c;
    }
  }
  return new NoCommand( _userManager, _channelManager, args, fd );
}
