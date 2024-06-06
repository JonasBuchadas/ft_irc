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

  while ( _args[pos] == ' ' && pos < _args.length() )
    pos++;
  if ( _args.length() > 1 && _args[pos] != '#' )
    return serverResponse( ERR_NOSUCHCHANNEL, "MODE" );

  std::string channelName = _args.substr( pos, _args.find( ' ', pos ) - pos );
  if ( !_channelManager->isOperator( channelName, _userFD ) )
    return serverResponse( ERR_CHANOPRIVSNEEDED, "MODE" );

  pos = _args.find( ' ', pos ) + 1;

  PreparedResponse pr = PreparedResponse();

  if ( pos >= _args.length()) {
    std::string modeResponse = _channelManager->getChannelModes( channelName );
    return serverResponse( RPL_CHANNELMODEIS, modeResponse );
  }
  while ( pos < _args.length() ) {
    char mode = _args[pos++];
    if ( mode == '+' || mode == '-' ) {
      add = ( mode == '+' );
      continue;
    }
    std::string target;
    if ( ( ( mode == 'k' || mode == 'l' ) && add ) || mode == 'o' ) {
      pos++;
      size_t spacePos = _args.find( ' ', pos );
      if ( spacePos != std::string::npos ) {
        target = _args.substr( pos, spacePos - pos );
        pos    = spacePos + 1;
      } else {
        target = _args.substr( pos );
        pos    = _args.length();
      }
    }
    Channel *channel = _channelManager->getChannel( channelName );
    if ( !channel )
      return serverResponse( ERR_NOSUCHCHANNEL, "MODE" );

    std::string m = "";
    m += mode;
    if (mode == 'o' )
    {
      if ( !_userManager->nickNameExists( target ) )
        return serverResponse( ERR_TARGETNOTINCHANNEL, channelName );
      if ( !_userManager->isLoggedIn( _userManager->getFdFromNick( target ) ) )
        return serverResponse( ERR_TARGETNOTAUTH, "" );
    }
    
    std::string answer;
    switch ( mode ) {
      case 'k':
        if ( add ) {
          channel->setPassword( target );
          answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
          channelName + " :set channel password");
          pr.allresponses[answer] = _channelManager->getChannel( channelName )->getAllMembersSansUser( _userFD, 0 );
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
          if ( !channel->isUser( _userManager->getFdFromNick( target ) ) )
            return serverResponse( ERR_TARGETNOTINCHANNEL, "MODE" );
          channel->addOperator( _userManager->getFdFromNick( target ) );
          channel->removeUser( _userManager->getFdFromNick( target ) );
          answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
          channelName + " :" + _userManager->getNick( _userFD ) + " gave operator status to " + target);
          pr.allresponses[answer].push_back( _userManager->getFdFromNick( target ) );
        }
        else
        {
          if ( !channel->isUser( _userManager->getFdFromNick( target ) ) )
            return serverResponse( ERR_TARGETNOTINCHANNEL, "MODE" );
          channel->removeOperator( _userManager->getFdFromNick( target ) );
          channel->addUser( _userManager->getFdFromNick( target ) );
          answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
          channelName + " :" + _userManager->getNick( _userFD ) + " removed operator status of " + target);
          pr.allresponses[answer].push_back( _userManager->getFdFromNick( target ) );
        }
        break;
      case 'i':
        channel->setInviteOnly( add );
        answer = genUserMsg( _userManager->getUser( _userFD ), "PRIVMSG " + \
        channelName + " :channel is now invite-only");
        pr.allresponses[answer].push_back( _userManager->getFdFromNick( target ) );
        break;
      case 't':
        channel->setTopicProtected( add );
        break;
      default:
        return serverResponse( ERR_UNKNOWNMODE, m );
    }
  }
  pr.allresponses[genUserMsg( _userManager->getUser( _userFD ), "MODE" + _args )].push_back( _userFD );
  return pr;
}
