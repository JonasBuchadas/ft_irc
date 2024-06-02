#include "commands/NamesCommand.hpp"

NamesCommand::NamesCommand( Authenticator *authenticator, ChannelManager *channelManager,
                            std::string args, int fd ) : ACommand( "NAMES", authenticator, channelManager, args, fd ) {}

NamesCommand::~NamesCommand() {
}

NamesCommand::NamesCommand( NamesCommand const &src ) : ACommand( src._authenticator, src._channelManager ) {
  *this = src;
}

NamesCommand &NamesCommand::operator=( NamesCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse NamesCommand::execute() const {
  PreparedResponse pr = PreparedResponse();
  pr.recipients.push_back( _userFD );
  if ( _args.length() <= 1 ) {
    pr.response = "Invalid string\n";
    return pr;
  }
  int i = 0;
  while (_args[i] == ' ')
    i++;
  if (_args[i] != '#')
  {
    pr.response = "Invalid channel identifier\n";
    return pr;
  }
  else if ( _channelManager->channelExists(&_args[i]) && !_channelManager->isUser( &_args[i], _userFD))
  {
    pr.response = "You don't belong to channels with this channel name\n";
    return pr;
  }
  else if ( !_channelManager->channelExists(&_args[i]) )
  {
    pr.response = "Channel doesn't exist\n";
    return pr;
  }
  std::vector<int> users = _channelManager->getChannel(&_args[i])->getAllUsers();
  std::string resp;
  resp = &_args[i];
  resp += " = :";
  for (int f = 0; f < (int)users.size(); f++)
  {
    resp += _authenticator->getNick(users[f]);
    if (f != (int)users.size() - 1)
      resp += ", ";
  }
  pr.response = genServerMsg(353, resp);
  return pr;
}
