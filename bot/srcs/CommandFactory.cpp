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

ACommand *makeNoCommand( BotManager *BotManager, std::string args, std::string nick ) {
  return new NoCommand( BotManager, args, nick );
}

ACommand *makeInviteCommand( BotManager *BotManager, std::string args, std::string nick ) {
  return new InviteCommand( BotManager, args, nick );
}

ACommand *makeAcceptCommand( BotManager *BotManager, std::string args, std::string nick ) {
  return new AcceptCommand( BotManager, args, nick );
}

ACommand *makeAskCommand( BotManager *BotManager, std::string args, std::string nick ) {
  return new AskCommand( BotManager, args, nick );
}

ACommand *makeAnswerCommand( BotManager *BotManager, std::string args, std::string nick ) {
  return new AnswerCommand( BotManager, args, nick );
}

ACommand *makeCloseCommand( BotManager *BotManager, std::string args, std::string nick ) {
  return new CloseCommand( BotManager, args, nick );
}

ACommand *makeViewCommand( BotManager *BotManager, std::string args, std::string nick ) {
  return new ViewCommand( BotManager, args, nick );
}

ACommand *makeReplyCommand( BotManager *BotManager, std::string args, std::string nick ) {
  return new ReplyCommand( BotManager, args, nick );
}


ACommand *CommandFactory::makeCommand( std::string commandName, BotManager *BotManager, std::string args, std::string nick ) {
  const std::string enumBotCmd[]  = { "INVITE", nick, "PART", "ASK", "ANSWER", "CLOSE", "VIEW", "REPLY" };
  const funcPtr     enumBotFunc[] = {
      &makeInviteCommand,
      &makeAcceptCommand,
      &makeAskCommand,
      &makeAnswerCommand,
      &makeCloseCommand,
      &makeViewCommand,
      &makeReplyCommand,
  };
  for ( int i = 0; i < 10; i++ ) {
    if ( commandName == enumBotCmd[i] ) {
      ACommand *c = ( enumBotFunc[i]( BotManager, args, nick ) );
      return c;
    }
  }
  return new NoCommand( BotManager, args, nick );
}
