#include "botcmds/AcceptCommand.hpp"

AcceptCommand::AcceptCommand( BotManager *BotManager, std::string args, std::string nick ) : ACommand( "ACCEPT", BotManager, args, nick ) {}

AcceptCommand::~AcceptCommand() {
}

AcceptCommand::AcceptCommand( AcceptCommand const &src ) : ACommand( src._BotManager ) {
  *this = src;
}

AcceptCommand &AcceptCommand::operator=( AcceptCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string AcceptCommand::execute() const {

  if (_args.find("353") == std::string::npos)
    return "";
  std::string beg = _args.substr(1);
  std::string names = beg.substr(_args.find(":") + 1);
  std::string channel = _args.substr(_args.find("#") + 1, beg.find(":") - 1);
  std::string channelName = channel.substr(0, channel.find(" "));
  Bot *bot = _BotManager->getBot( channelName );
  if (bot == NULL)
    return "PRIVMSG #" + channelName + " :Bot doesn't exist. Nothing to do!\n";
  for (int i = 0; i < (int)names.size(); i++)
  {
    if (names[i] == '@' || names[i] == '%')
    {
      i++;
      int start = i;
      while ( names[i] != ',' && names[i] != '\0' )
        i++;
      std::string user = names.substr(start, i - start - 1);
      if (bot->getUser( user ) == "")
        bot->addUser( user );
    }
  }
  return "PRIVMSG #" + channelName + " :Users successfully updated!\n";
}
