#include "botcmds/DismissCommand.hpp"

DismissCommand::DismissCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "DISMISS", authenticator, args, fd ) {}

DismissCommand::~DismissCommand() {
}

DismissCommand::DismissCommand( DismissCommand const &src ) : ACommand( src._authenticator ) {
  *this = src;
}

DismissCommand &DismissCommand::operator=( DismissCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string DismissCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  if ( !_authenticator->getUser( _userFD ) || !_authenticator->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string name, leftovers;
  args >> name >> leftovers;

  if ( !leftovers.empty() )
    return "Invalid string\n";

  if ( !_authenticator->isValidArg( name ) )
    return "Invalid bot name\n";

  Bot *bot = _authenticator->getBot( name );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if (bot->getOper( _userFD ) != -1 ) {
    _authenticator->getBotManager()->delBot( name );
    return "Bot successfully deleted\n";
  }
  else
    return "You are not this bot's operator. Nothing to do\n";
}
