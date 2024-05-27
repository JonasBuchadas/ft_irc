#include "botcmds/GrantCommand.hpp"

GrantCommand::GrantCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "GRANT", authenticator, args, fd ) {}

GrantCommand::~GrantCommand() {
}

GrantCommand::GrantCommand( GrantCommand const &src ) : ACommand( src._authenticator ) {
  *this = src;
}

GrantCommand &GrantCommand::operator=( GrantCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string GrantCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  if ( !_authenticator->getUser( _userFD ) || !_authenticator->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can use bots. Authenticate first!\n";

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
  bot->getUser( _authenticator->getFdFromNick( users )) == -1 )
  {
    _authenticator->getBotManager()->getBot( name )->addUser( _authenticator->getFdFromNick( users ) );
    return "Bot user status successfully granted\n";
  }
  else if (bot->getOper( _userFD ) && !users.empty() \
  && _authenticator->nickNameExists( _userFD, users ) && \
  bot->getUser( _authenticator->getFdFromNick( users )) != -1 )
  {
    _authenticator->getBot( name )->addOper( _authenticator->getFdFromNick( users ) );
    return "Bot operator status successfully granted\n";
  }
  return "Invalid grantee. Nothing to do\n";
}
