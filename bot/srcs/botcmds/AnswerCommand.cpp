#include "botcmds/AnswerCommand.hpp"

AnswerCommand::AnswerCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "ANSWER", BotManager, args, nick ) {}

AnswerCommand::~AnswerCommand() {
}

AnswerCommand::AnswerCommand( AnswerCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

AnswerCommand &AnswerCommand::operator=( AnswerCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string AnswerCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  std::stringstream args(_args);
  std::string channel, id, msg, leftovers;
  args >> channel >> id >> msg >> leftovers;

  if ( !leftovers.empty() || id.empty() || msg.empty() )
    return "Invalid string\n";

  Bot *bot = _BotManager->getBot( channel );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( !bot->getAsk( id ) )
    return "Answered invalid question. Nothing to do\n";
  else if ( bot->getAsk( id ) && !bot->getIsOpen( id ) )
    return "You are not allowed to write to this list right now\n";

  std::stringstream m(msg);
  std::string s;
  m >> s;
  if ( s.empty() )
    return "Invalid string\n";
  _BotManager->getBot( channel )->setAsk( id, s.substr(0, s.find("\n") - 1) );
  _BotManager->getBot( channel )->setIsOpen( id, true );
  return "Question and answer successfully set\n";
}
