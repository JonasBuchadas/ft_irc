#include "commands/NamesCommand.hpp"

NamesCommand::NamesCommand( UserManager *userManager, ChannelManager *channelManager,
                            std::string args, int fd ) : ACommand( "NAMES", userManager, channelManager, args, fd ) {}

NamesCommand::~NamesCommand() {
}

NamesCommand::NamesCommand( NamesCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
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
  while ( _args[i] == ' ' )
    i++;
  if ( _args[i] != '#' ) {
    pr.response = "Invalid channel identifier\n";
    return pr;
  } else if ( _channelManager->channelExists( &_args[i] ) && \
  !(_channelManager->isOperator( &_args[i], _userFD) || _channelManager->isUser( &_args[i], _userFD ) ) ) {
    pr.response = "You don't belong to channels with this channel name\n";
    return pr;
  } else if ( !_channelManager->channelExists( &_args[i] ) ) {
    pr.response = "Channel doesn't exist\n";
    return pr;
  }
  std::vector<int> opers = _channelManager->getChannel( &_args[i] )->getAllOperators();
  std::vector<int> users = _channelManager->getChannel( &_args[i] )->getAllUsers();
  std::string      resp;
  resp = &_args[i];
  resp += " = :";
  for ( int f = 0; f < (int)opers.size(); f++ ) {
    resp += _userManager->getNick( opers[f] );
    if ( f != (int)opers.size() - 1 )
      resp += ", ";
  }
  for ( int f = 0; f < (int)users.size(); f++ ) {
    if (opers.size() > 0 || f > 0)
      resp += ", ";
    resp += _userManager->getNick( users[f] );
  }
  pr.response = genServerMsg( 353, resp );
  return pr;
}
