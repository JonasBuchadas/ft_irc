#include "botcmds/ViewCommand.hpp"

ViewCommand::ViewCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "VIEW", BotManager, args, nick ) {}

ViewCommand::~ViewCommand() {
}

ViewCommand::ViewCommand( ViewCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

ViewCommand &ViewCommand::operator=( ViewCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string ViewCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  // if ( !_BotManager->getUser( _usernick ) || !_BotManager->getUser( _usernick )->getLoggedIn() )
  //   return "Only authenticated users can use bots. Authenticate first!\n";

  std::stringstream args(_args);
  std::string channel, ask, id, leftovers;
  args >> channel >> ask >> id >> leftovers;

  if ( channel.empty() || ask.empty() || !leftovers.empty())
    return "Invalid string\n";

  if ( !_BotManager->isValidArg( channel ) )
    return "Invalid bot channel\n";

  Bot *bot = _BotManager->getBot( channel );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( !_BotManager->getBot( channel )->getAsk( ask ) )
    return "Question doesn't exist. Nothing to do\n";

  std::stringstream num(id);
  int i = -1;
  num >> i;
  std::string resp;
  resp += "Ask " + ask + ":\n";
  if (i != -1 && i < (int)_BotManager->getBot( channel )->getAsk( ask ))
    resp += "#" + id + ": " + _BotManager->getBot( channel )->getOption( ask, i ) + "\n";
  else
  {
    for (int j = 0; j < (int)_BotManager->getBot( channel )->getAsk( ask ); j++)
    {
      std::stringstream num;
      num << j;
      num >> id;
      resp += "#" + id + ": " + _BotManager->getBot( channel )->getOption( ask, j ) + "\n";
    }
  }
  resp += "Ask viewed all selected answers to selected question\n";
  return resp;
}
