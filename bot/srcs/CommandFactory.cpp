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

ACommand *makeNoCommand( std::string args, std::string nick ) {
  return new NoCommand( args, nick );
}

ACommand *makeInviteCommand( std::string args, std::string nick ) {
  return new InviteCommand( args, nick );
}

ACommand *makeShootCommand( std::string args, std::string nick ) {
  return new ShootCommand( args, nick );
}

ACommand *makeNamesCommand( std::string args, std::string nick ) {
  return new NamesCommand( args, nick );
}


ACommand *CommandFactory::makeCommand( std::string commandName, std::string args, std::string nick ) {
  const std::string enumBotCmd[]  = { "INVITE", "SHOOT", nick };
  const funcPtr     enumBotFunc[] = {
      &makeInviteCommand,
      &makeShootCommand,
      &makeNamesCommand,
  };
  for ( int i = 0; i < 3; i++ ) {
    if ( commandName == enumBotCmd[i] ) {
      ACommand *c = ( enumBotFunc[i]( args, nick ) );
      return c;
    }
  }
  return new NoCommand( args, nick );
}
