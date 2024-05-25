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

ACommand *makeUserCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new UserCommand( authenticator, args, fd );
}

ACommand *makePassCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new PassCommand( authenticator, args, fd );
}

ACommand *makeNickCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new NickCommand( authenticator, args, fd );
}

ACommand *CommandFactory::makeCommand( Authenticator *authenticator, int fd, std::string commandName, std::string args ) {
  const std::string enumCommand[] = { "USER", "PASS", "NICK" };
  const funcPtr     enumFunc[]    = {
      &makeUserCommand,
      &makePassCommand,
      &makeNickCommand,
  };
  for ( int i = 0; i < 3; i++ ) {
    if ( commandName == enumCommand[i] ) {
      ACommand *c = ( enumFunc[i]( authenticator, args, fd ) );
      return c;
    }
  }
  return new NoCommand( authenticator, args, fd );
}
