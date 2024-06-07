#include "commands/ModeCommand.hpp"

ModeCommand::ModeCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "MODE", userManager, channelManager, args, fd ) {}

ModeCommand::~ModeCommand() {
}

ModeCommand::ModeCommand( ModeCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

ModeCommand &ModeCommand::operator=( ModeCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse ModeCommand::execute() const {
  bool   add = true;
  size_t pos = 0;

  if ( !_userManager->isLoggedIn( _userFD ) )
    return serverResponse( ERR_NOTREGISTERED, "MODE" );

  std::stringstream c( _args );
  std::string channelName, arg, target, invalidArg;
  c >> channelName >> arg >> target >> invalidArg;

  if ( !_channelManager->channelExists( channelName ) )
    return serverResponse( ERR_NOSUCHCHANNEL, channelName );

  if ( !_channelManager->isOperator( channelName, _userFD ) )
    return serverResponse( ERR_CHANOPRIVSNEEDED, channelName );

  if ( arg.empty() ) {
    std::string modeResponse = _channelManager->getChannelModes( channelName );
    return serverResponse( RPL_CHANNELMODEIS, channelName + " " + modeResponse );
  }

  if ( (arg[0] == '+' || arg[0] == '-') && !arg[1] )
    return serverResponse( ERR_NEEDMOREPARAMS, "MODE" );
  PreparedResponse pr = PreparedResponse();

  add = ( arg[pos++] == '+' );
  char m = arg[pos];
  std::string mode = &arg[pos];
  Channel *channel = _channelManager->getChannel( channelName );
  if ( !channel )
    return serverResponse( ERR_NOSUCHCHANNEL, channelName );

  if (m == 'o' )
  {
    if ( !_userManager->nickNameExists( target ) )
      return serverResponse( ERR_TARGETNOTINCHANNEL, channelName );
    if ( !_userManager->isLoggedIn( _userManager->getFdFromNick( target ) ) )
      return serverResponse( ERR_TARGETNOTAUTH, "" );
  }
    
  std::string answer;
  switch ( m ) {
    case 'k':
      if ( add && !target.empty()) {
        channel->setPassword( target );
        answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
        channelName + " :set channel password");
        pr.allresponses[answer] = _channelManager->getChannel( channelName )->getAllMembersSansUser( _userFD );
      }
      else
        channel->setPassword( "" );
      break;
    case 'l':
      if ( add )
        channel->setMaxUsers( std::atoi( target.c_str() ) );
      else
        channel->setMaxUsers( 0 );
      break;
    case 'o':
      if ( add )
      {
        if ( !channel->isUser( _userManager->getFdFromNick( target ) ) && channel->isOperator( _userManager->getFdFromNick( target ) ) )
          return serverResponse( ERR_TARGETISOPER, "MODE" );
        channel->addOperator( _userManager->getFdFromNick( target ) );
        channel->removeUser( _userManager->getFdFromNick( target ) );
        answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
        channelName + " :" + _userManager->getNick( _userFD ) + " gave operator status to " + target);
        pr.allresponses[answer] = _channelManager->getChannel( channelName )->getAllMembers();
      }
      else
      {
        if ( !channel->isOperator( _userManager->getFdFromNick( target ) ) )
          return serverResponse( ERR_TARGETNOTOPER, "MODE" );
        channel->removeOperator( _userManager->getFdFromNick( target ) );
        channel->addUser( _userManager->getFdFromNick( target ) );
        answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
        channelName + " :" + _userManager->getNick( _userFD ) + " removed operator status of " + target);
        pr.allresponses[answer] = _channelManager->getChannel( channelName )->getAllMembers();
      }
      break;
    case 'i':
      channel->setInviteOnly( add );
      if (add)
        answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
        channelName + " :channel is now invite-only");
      else
        answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
        channelName + " :channel is no longer invite-only");
      pr.allresponses[answer] = _channelManager->getChannel( channelName )->getAllMembers();
      break;
    case 't':
      channel->setTopicProtected( add );
      break;
    default:
      return serverResponse( ERR_UNKNOWNMODE, mode + ":is unknown mode char for " + channelName );
  }
  pr.allresponses[genUserMsg( _userManager->getUser( _userFD ), "MODE" + _args )].push_back( _userFD );
  return pr;
}
