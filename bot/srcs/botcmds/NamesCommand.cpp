#include "botcmds/NamesCommand.hpp"

NamesCommand::NamesCommand( std::string args, std::string Names ) : ACommand( "NAMES", args, Names ) {}

NamesCommand::~NamesCommand() {
}

NamesCommand::NamesCommand( NamesCommand const &src ) : ACommand() {
  *this = src;
}

NamesCommand &NamesCommand::operator=( NamesCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string NamesCommand::execute() const {
  if (_args.find("353") == std::string::npos)
    return "";
  std::string strstart = _args.substr(_args.find("353"));
  std::string names = strstart.substr(strstart.find(":") + 1);
  std::string channel = strstart.substr(strstart.find("#"), strstart.find(":") - 1);
  std::string channelName = channel.substr(0, channel.find(" "));
  std::vector<std::string> allNames;
  for (int i = 0; i < (int)names.size(); i++)
  {
    while (names[i] == ',' || names[i] == ' ')
      i++;
    if (names[i] == '\0')
      break ;
    int start = i;
    while ( names[i] && names[i] != ',' && names[i] != '\0' )
      i++;
    std::string user = names.substr(start, i - start);
    if ( user != _usernick )
      allNames.push_back(user);
  }
  return "KICK " + channelName + " " + allNames[rand() % allNames.size()] + "\r\n";
}