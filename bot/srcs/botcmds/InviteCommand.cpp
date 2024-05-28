#include "botcmds/InviteCommand.hpp"

InviteCommand::InviteCommand( BotManager *BotManager, std::string args, std::string Invite ) : ACommand( "INVITE", BotManager, args, Invite ) {}

InviteCommand::~InviteCommand() {
}

InviteCommand::InviteCommand( InviteCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

InviteCommand &InviteCommand::operator=( InviteCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string InviteCommand::execute() const {
  std::string channel;
  if (_args.find("#") != std::string::npos)
  {
    int start = _args.find("#") + 1;
    channel = _args.substr(start, _args.find("\n") - start - 1);
  }
  else
    return "Unknown channel name";
  Bot *bot = _BotManager->getBot( channel );
  if ( bot == NULL ) {
    bot = new Bot();
    _BotManager->addBot( channel, bot );
  }
  else
    return "Already in channel";
  return "JOIN #" + channel + "\n";
}
