#include "botcmds/OpenCommand.hpp"

OpenCommand::OpenCommand( BotManager *BotManager, std::string args, int fd ) : ACommand( "OPEN", BotManager, args, fd ) {}

OpenCommand::~OpenCommand() {
}

OpenCommand::OpenCommand( OpenCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

OpenCommand &OpenCommand::operator=( OpenCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string OpenCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  if ( !_BotManager->getUser( _userFD ) || !_BotManager->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string name, id, leftovers;
  args >> name >> id >> leftovers;

  if ( !leftovers.empty() || id.empty() )
    return "Invalid string\n";

  if ( !_BotManager->isValidArg( name ) )
    return "Invalid bot name\n";

  Bot *bot = _BotManager->getBot( name );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( bot->getOper( _userFD ) == -1 )
    return "You are not this bot's operator. Nothing to do\n";

  if ( bot->getIsOpen( id ) )
    return "Bot already accepting user input. Nothing to do\n";

  _BotManager->getBot( name )->setIsOpen( id, true );
  return "Bot set to accept user input in alias " + id + "\n";
}
