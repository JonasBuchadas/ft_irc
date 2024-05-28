#include "botcmds/ReplyCommand.hpp"

ReplyCommand::ReplyCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "REPLY", BotManager, args, nick ) {}

ReplyCommand::~ReplyCommand() {
}

ReplyCommand::ReplyCommand( ReplyCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

ReplyCommand &ReplyCommand::operator=( ReplyCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string ReplyCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  std::stringstream args(_args);
  std::string channel, ask, id, leftovers;
  args >> channel >> ask >> id >> leftovers;

  if ( channel.empty() || channel.empty() || ask.empty() || !leftovers.empty())
    return "Invalid string\n";

  Bot *bot = _BotManager->getBot( channel );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( !_BotManager->getBot( channel )->getAsk( ask ) )
    return "Question doesn't exist. Nothing to do\n";

  std::stringstream num(id);
  int i = -1;
  num >> i;
  std::string resp;
  resp += "Question " + ask + ":\n";
  if (i != -1 && i < (int)_BotManager->getBot( channel )->getAsk( ask ))
    resp += "#" + id + ": " + _BotManager->getBot( channel )->getOption( ask, i ) + "\n";
  else
  {
    i = rand() % _BotManager->getBot( channel )->getAsk( ask );
    std::stringstream num;
    num << i;
    num >> id;
    resp += "#" + id + ": " + _BotManager->getBot( channel )->getOption( ask, i ) + "\n";
  }
  return resp;
}
