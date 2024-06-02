#include "botcmds/ShootCommand.hpp"

ShootCommand::ShootCommand( std::string args, std::string nick ) : ACommand( "SHOOT", args, nick ) {}

ShootCommand::~ShootCommand() {
}

ShootCommand::ShootCommand( ShootCommand const &src ) : ACommand() {
  *this = src;
}

ShootCommand &ShootCommand::operator=( ShootCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string ShootCommand::execute() const {
  if (_args.find("353") == std::string::npos)
    return "";
  else
  {
    std::string channel = _args.substr(_args.find("#") + 1, _args.find(":") - 1);
    return "NAMES #" + channel + "\n";
  }
  std::string names = _args.substr(_args.find(":") + 1);
  std::string channel = _args.substr(_args.find("#") + 1, _args.find(":") - 1);
  std::string channelName = channel.substr(0, channel.find(" "));
  std::vector<std::string> allNames;
  for (int i = 0; i < (int)names.size(); i++)
  {
    while (names[i] == ',' || names[i] == ' ')
      i++;
    if (names[i] == '\0')
      break ;
    int start = i;
    while ( names[i] != ',' && names[i] != '\0' )
      i++;
    std::string user = names.substr(start, i - start - 1);
    allNames[allNames.size()] = user;
  }
  
  return "KICK #" + channelName + " " + allNames[rand() % allNames.size()] + "\n";
}
