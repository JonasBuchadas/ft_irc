#include "botcmds/RenameCommand.hpp"

RenameCommand::RenameCommand( BotManager *BotManager, std::string args, int fd ) : ACommand( "RENAME", BotManager, args, fd ) {}

RenameCommand::~RenameCommand() {
}

RenameCommand::RenameCommand( RenameCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

RenameCommand &RenameCommand::operator=( RenameCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string RenameCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  if ( !_BotManager->getUser( _userFD ) || !_BotManager->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string name, newname, leftovers;
  args >> name >> newname >> leftovers;

  if ( (!leftovers.empty() && newname != ":") || newname.empty() || _args.find(":") == std::string::npos)
    return "Invalid string\n";
  else if (!leftovers.empty() && newname == ":")
    newname = leftovers;
  else if (leftovers.empty() && newname[0] == ':')
    newname = newname.substr(1);
  if ( !_BotManager->isValidArg( newname ) )
    return "New bot name contains invalid characters\n";

  if ( _BotManager->getUser( _userFD )->getNick() == newname ) {
    return "New name coincides with user. Bot not renamed\n";
  }

  Bot *bot = _BotManager->getBot( name );
  if ( bot == NULL ) {
    return "Bot doesn't exist. Nothing to do!\n";
  }
  else if (bot->getOper( _userFD ) == -1 ) {
    return "You are not this bot's operator. Nothing to do\n";
  }
  else {
    Bot *replace = new Bot(*bot);
    _BotManager->getBotManager()->delBot( name );
    replace->setName( newname );
    _BotManager->getBotManager()->addBot( newname, replace );
    return "Bot successfully renamed\n";
  }
  return "Bot conditions not changed. Nothing to do!\n";
}
