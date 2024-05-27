#include "botcmds/AliasCommand.hpp"

AliasCommand::AliasCommand( BotManager *BotManager, std::string args, int fd ) : ACommand( "ALIAS", BotManager, args, fd ) {}

AliasCommand::~AliasCommand() {
}

AliasCommand::AliasCommand( AliasCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

AliasCommand &AliasCommand::operator=( AliasCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string AliasCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  if ( !_BotManager->getUser( _userFD ) || !_BotManager->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can use bots. Authenticate first!\n";

  if ( _args.find(":") == std::string::npos )
    return "Invalid string\n";

  std::stringstream args(_args.substr(0, _args.find(":") - 1));
  std::string name, id;
  args >> name >> id;

  if ( name.empty() || id.empty())
    return "Invalid string\n";

  if ( !_BotManager->isValidArg( name ) )
    return "Invalid bot name\n";

  Bot *bot = _BotManager->getBot( name );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( ( !bot->getIsOpen( id ) && bot->getOper( _userFD ) == -1 ) \
  ||  ( bot->getIsOpen( id ) && bot->getUser( _userFD ) == -1 ))
    return "You are not allowed to write to this bot right now\n";

  std::string msg = _args.substr(_args.find(":") + 1, _args.find("\n") - 1);
  std::stringstream m(msg);
  std::string s;
  m >> s;
  if ( !msg.length() || s.empty() )
    return "Invalid alias. Nothing to do\n";

  _BotManager->getBot( name )->setAlias( id , msg );
  return "Alias successfully set\n";
}
