#include "botcmds/ReplyCommand.hpp"

ReplyCommand::ReplyCommand( BotManager *BotManager, std::string args, int fd ) : ACommand( "REPLY", BotManager, args, fd ) {}

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

  if ( !_BotManager->getUser( _userFD ) || !_BotManager->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string name, alias, id, leftovers;
  args >> name >> alias >> id >> leftovers;

  if ( name.empty() || alias.empty() || !leftovers.empty())
    return "Invalid string\n";

  if ( !_BotManager->isValidArg( name ) )
    return "Invalid bot name\n";

  Bot *bot = _BotManager->getBot( name );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( bot->getOper( _userFD ) == -1 )
    return "You are not this bot's operator. Nothing to do\n";
  else if ( !_BotManager->getBot( name )->getAlias( alias ) )
    return "Alias doesn't exist. Nothing to do\n";

  std::stringstream num(id);
  int i = -1;
  num >> i;
  std::string resp;
  resp += "Alias " + alias + ":\n";
  if (i != -1 && i < (int)_BotManager->getBot( name )->getAlias( alias ))
    resp += "#" + id + ": " + _BotManager->getBot( name )->getOption( alias, i ) + "\n";
  else
  {
    i = rand() % _BotManager->getBot( name )->getAlias( alias );
    std::stringstream num;
    num << i;
    num >> id;
    resp += "#" + id + ": " + _BotManager->getBot( name )->getOption( alias, i ) + "\n";
  }
  return resp;
}
