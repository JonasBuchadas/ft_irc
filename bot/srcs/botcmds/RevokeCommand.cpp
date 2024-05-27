#include "botcmds/RevokeCommand.hpp"

RevokeCommand::RevokeCommand( BotManager *BotManager, std::string args, int fd ) : ACommand( "REVOKE", BotManager, args, fd ) {}

RevokeCommand::~RevokeCommand() {
}

RevokeCommand::RevokeCommand( RevokeCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

RevokeCommand &RevokeCommand::operator=( RevokeCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string RevokeCommand::execute() const {
    if (_args.length() <= 1)
    return "Invalid string\n";

  if ( !_BotManager->getUser( _userFD ) || !_BotManager->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can  use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string name, users, leftovers;
  args >> name >> users >> leftovers;

  if ( !leftovers.empty() )
    return "Invalid string\n";

  if ( !_BotManager->isValidArg( name ) )
    return "Invalid bot name\n";

  Bot *bot = _BotManager->getBot( name );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( !bot->getOper( _userFD ) )
    return "You are not this bot's operator. Nothing to do\n";
  else if (bot->getOper( _userFD ) && !users.empty() \
  && bot->getOper( _BotManager->getFdFromNick( users ) != -1 ))
  {
    _BotManager->getBot( name )->rmvOper( _BotManager->getFdFromNick( users ) );
    return "Bot operator status successfully revoked\n";
  }
  else if (bot->getOper( _userFD ) && !users.empty() \
  && bot->getOper( _BotManager->getFdFromNick( users ) == -1 ) \
  && bot->getUser( _BotManager->getFdFromNick( users ) != -1 ))
  {
    _BotManager->getBot( name )->rmvUser( _BotManager->getFdFromNick( users ) );
    return "Bot user status successfully revoked\n";
  }
  return "Invalid grantee. Nothing to do\n";
}
