#include "CommandFactory.hpp"

CommandFactory::CommandFactory() {}

CommandFactory::~CommandFactory() {
}

CommandFactory::CommandFactory( CommandFactory const &src ) {
  *this = src;
}

CommandFactory &CommandFactory::operator=( CommandFactory const &src ) {
  if ( this == &src )
    return ( *this );
  return ( *this );
}

ACommand *makeUserCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new UserCommand( authenticator, channelmanager, args, fd );
}

ACommand *makePassCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new PassCommand( authenticator, channelmanager, args, fd );
}

ACommand *makeNickCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new NickCommand( authenticator, channelmanager, args, fd );
}

ACommand *makePrivCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new PrivCommand( authenticator, channelmanager, args, fd );
}

ACommand *makeJoinCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new JoinCommand( authenticator, channelmanager, args, fd );
}

ACommand *makeKickCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new KickCommand( authenticator, channelmanager, args, fd );
}

ACommand *makeInviteCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new InviteCommand( authenticator, channelmanager, args, fd );
}

ACommand *makePartCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new PartCommand( authenticator, channelmanager, args, fd );
}

ACommand *makeNamesCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new NamesCommand( authenticator, channelmanager, args, fd );
}

ACommand *makeModeCommand( Authenticator *authenticator, ChannelManager *channelmanager, std::string args, int fd ) {
  return new ModeCommand( authenticator, channelmanager, args, fd );
}

ACommand *CommandFactory::makeCommand( Authenticator  *authenticator,
                                       ChannelManager *channelmanager, int fd, std::string commandName, std::string args ) {
  const std::string enumCommand[] = { "USER", "PASS", "NICK", "PRIVMSG", "JOIN", "KICK", "INVITE", "PART", "NAMES", "MODE" };
  const funcPtr     enumFunc[]    = {
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
  for ( int i = 0; i < 5; i++ ) {
    if ( commandName == enumCommand[i] ) {
      ACommand *c = ( enumFunc[i]( authenticator, channelmanager, args, fd ) );
      return c;
    }
  }
  return new NoCommand( authenticator, channelmanager, args, fd );
}
