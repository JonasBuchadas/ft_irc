#include "botcmds/NickCommand.hpp"

NickCommand::NickCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "NICK", BotManager, args, nick ) {}

NickCommand::~NickCommand() {
}

NickCommand::NickCommand( NickCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

NickCommand &NickCommand::operator=( NickCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string NickCommand::execute() const {
  std::string channel;
  if (_args.find("#") != std::string::npos)
    channel = _args.substr(_args.find("#"));
  else
    return "Unknown channel name";

  Bot *bot = _BotManager->getBot( channel );
  if (bot->getUser( _usernick ) != "")
    return "User already accepted. Nothing to do!\n";
  else
  {
    bot->rmvUser( _usernick );
    std::string equals = "is now known as ";
    if ( _args.find(equals) != std::string::npos )
      bot->addUser( _args.substr(_args.find(equals) + equals.size()) );
    else
      return "Invalid new username\n";
  }
  return "User accepted!\n";
}
