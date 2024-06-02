#include "botcmds/InviteCommand.hpp"

InviteCommand::InviteCommand( std::string args, std::string Invite ) : ACommand( "INVITE", args, Invite ) {}

InviteCommand::~InviteCommand() {
}

InviteCommand::InviteCommand( InviteCommand const &src ) : ACommand() {
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
  std::string other_args = "";
  if (_args.find("#") != std::string::npos)
  {
    int start = _args.find("#");
    channel = _args.substr(start, _args.find_first_of(" \n\r") - start - 1);
    other_args = _args.substr(_args.find_first_of(" \n\r"));
    if (_args[0] == '\n')
      other_args = "";
  }
  else
    return "Unknown channel name";
  return "JOIN " + channel + "\n";
}
