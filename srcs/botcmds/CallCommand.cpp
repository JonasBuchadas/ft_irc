#include "botcmds/CallCommand.hpp"

CallCommand::CallCommand( Authenticator *authenticator, std::string args, int fd ) : ACommand( "CALL", authenticator, args, fd ) {}

CallCommand::~CallCommand() {
}

CallCommand::CallCommand( CallCommand const &src ) : ACommand( src._authenticator ) {
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

  if ( !_authenticator->getUser( _userFD ) || !_authenticator->getUser( _userFD )->getLoggedIn() )
    return "Only authenticated users can use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string name, users, leftovers;
  args >> name >> users >> leftovers;

  if ( !leftovers.empty() )
    return "Invalid string\n";

  if ( !_authenticator->isValidArg( name ) )
    return "Bot name contains invalid characters\n";

  if ( _authenticator->nickNameExists( _userFD, name ) \
   || _authenticator->getUser( _userFD )->getNick() == name) {
    return "Name coincides with user. Bot not created\n";
  }

  Bot *bot = _authenticator->getBot( name );
  if ( bot == NULL ) {
    bot = new Bot();
    bot->setName( name );
    bot->addOper( _userFD );
    bot->getAllUsers().push_back( _userFD );
    if ( !users.empty() && _authenticator->nickNameExists( _userFD, users ) )
      bot->getAllUsers().push_back( _authenticator->getFdFromNick(users) );
    _authenticator->getBotManager()->addBot( name, bot );
    return "Bot successfully created\n";
  }
  else if (bot->getOper( _userFD ) && !users.empty() \
  && _authenticator->nickNameExists( _userFD, users ) && bot->getUser( _authenticator->getFdFromNick( users ) == -1 ))
  {
    bot->getAllUsers().push_back( _authenticator->getFdFromNick( users ) );
    return "Bot successfully updated\n";
  }
  else if (!bot->getOper( _userFD ))
    return "Botname taken! Not created\n";
  return "Bot conditions not changed. Nothing to do!\n";
}
