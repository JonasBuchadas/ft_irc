#include "botcmds/RevokeCommand.hpp"

RevokeCommand::RevokeCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "REVOKE", authenticator, args, fd ) {}

RevokeCommand::~RevokeCommand() {
}

RevokeCommand::RevokeCommand( RevokeCommand const &src ) : ACommand( src._authenticator ) {
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

  if ( !_authenticator->getUser( _userFD ) || !_authenticator->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can  use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string name, users, leftovers;
  args >> name >> users >> leftovers;

  if ( !leftovers.empty() )
    return "Invalid string\n";

  if ( !_authenticator->isValidArg( name ) )
    return "Invalid bot name\n";

  Bot *bot = _authenticator->getBot( name );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( !bot->getOper( _userFD ) )
    return "You are not this bot's operator. Nothing to do\n";
  else if (bot->getOper( _userFD ) && !users.empty() \
  && _authenticator->nickNameExists( _userFD, users ) && \
  bot->getOper( _authenticator->getFdFromNick( users ) != -1 ))
  {
    _authenticator->getBot( name )->rmvOper( _authenticator->getFdFromNick( users ) );
    return "Bot operator status successfully revoked\n";
  }
  else if (bot->getOper( _userFD ) && !users.empty() \
  && _authenticator->nickNameExists( _userFD, users ) && \
  bot->getOper( _authenticator->getFdFromNick( users ) == -1 ) && \
  bot->getUser( _authenticator->getFdFromNick( users ) != -1 ))
  {
    _authenticator->getBot( name )->rmvUser( _authenticator->getFdFromNick( users ) );
    return "Bot user status successfully revoked\n";
  }
  return "Invalid grantee. Nothing to do\n";
}
