#include "botcmds/RmidCommand.hpp"

RmidCommand::RmidCommand( BotManager *BotManager, std::string args, int fd ) : ACommand( "RMID", BotManager, args, fd ) {}

RmidCommand::~RmidCommand() {
}

RmidCommand::RmidCommand( RmidCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

RmidCommand &RmidCommand::operator=( RmidCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string RmidCommand::execute() const {
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

  std::stringstream num(id);
  int i = -1;
  num >> i;
  _BotManager->getBot( name )->rmAlias( name, i );
  return "Alias successfully removed\n";
}
