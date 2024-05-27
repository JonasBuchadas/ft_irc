#include "botcmds/CallCommand.hpp"

CallCommand::CallCommand( BotManager *BotManager, std::string args, int fd ) : ACommand( "CALL", BotManager, args, fd ) {}

CallCommand::~CallCommand() {
}

CallCommand::CallCommand( CallCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

CallCommand &CallCommand::operator=( CallCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string CallCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  if ( !_BotManager->getUser( _userFD ) || !_BotManager->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string name, users, leftovers;
  args >> name >> users >> leftovers;

  if ( !leftovers.empty() )
    return "Invalid string\n";

  if ( !_BotManager->isValidArg( name ) )
    return "Bot name contains invalid characters\n";

  if ( _BotManager->getUser( _userFD )->getNick() == name) {
    return "Name coincides with user. Bot not created\n";
  }

  Bot *bot = _BotManager->getBot( name );
  if ( bot == NULL ) {
    bot = new Bot();
    bot->setName( name );
    bot->addOper( _userFD );
    bot->getAllUsers().push_back( _userFD );
    if ( !users.empty() && bot->getAllUsers().push_back( _BotManager->getFdFromNick(users)) );
    _BotManager->getBotManager()->addBot( name, bot );
    return "Bot successfully created\n";
  }
  else if ( bot->getOper( _userFD ) )
  {
    bot->getAllUsers().push_back( _BotManager->getFdFromNick( users ) );
    return "Bot successfully updated\n";
  }
  else if ( !bot->getOper( _userFD ) )
    return "Botname taken! Not created\n";
  return "Bot conditions not changed. Nothing to do!\n";
}
