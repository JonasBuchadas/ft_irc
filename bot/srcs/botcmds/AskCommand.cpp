#include "botcmds/AskCommand.hpp"

AskCommand::AskCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "ASK", BotManager, args, nick ) {}

AskCommand::~AskCommand() {
}

AskCommand::AskCommand( AskCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

AskCommand &AskCommand::operator=( AskCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string AskCommand::execute() const {
  if (_args.length() <= 1)
    return "Invalid string\n";

  if ( _args.find(":") == std::string::npos )
    return "Invalid string\n";

  std::stringstream args(_args.substr(0, _args.find(":") - 1));
  std::string channel, id;
  args >> channel >> id;

  if ( channel.empty() || id.empty())
    return "Invalid string\n";

  Bot *bot = _BotManager->getBot( channel );
  if ( bot == NULL )
    return "Bot doesn't exist. Nothing to do!\n";
  else if ( bot->getAsk( id ) && !bot->getIsOpen( id ) )
    return "You are not allowed to write to this list right now\n";

  std::string msg = _args.substr(_args.find(":") + 1, _args.find("\n") - 1);
  std::stringstream m(msg);
  std::string s;
  m >> s;
  if ( !msg.length() || s.empty() )
    return "Invalid answer. Nothing to do\n";

  _BotManager->getBot( channel )->setAsk( id , msg.substr(0, msg.find("\n") - 1) );
  return "Ask successfully set\n";
}
