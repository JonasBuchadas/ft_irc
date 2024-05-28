#include "botcmds/CloseCommand.hpp"

CloseCommand::CloseCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "CLOSE", BotManager, args, nick ) {}

CloseCommand::~CloseCommand() {
}

CloseCommand::CloseCommand( CloseCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

CloseCommand &CloseCommand::operator=( CloseCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string CloseCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  std::stringstream args(_args);
  std::string name, id, leftovers;
  args >> name >> id >> leftovers;

  if ( !leftovers.empty() )
    return "Invalid string\n";

  Bot *bot = _BotManager->getBot( name );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( !bot->getIsOpen( id ) )
    return "Bot not accepting user input. Nothing to do\n";

  _BotManager->getBot( name )->setIsOpen( id, false );
  return "Bot set to not longer accept user input in question " + id + "\n";
}
