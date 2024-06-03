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
  bool add = true;
  size_t pos = 0;
  PreparedResponse pr = PreparedResponse();

  pr.recipients.push_back( _userFD );
  if ( !_userManager->isLoggedIn( _userFD ) ) {
    pr.response = "Not logged in\n";
    return pr;
  }
  while ( _args[pos] == ' ' && pos < _args.length() )
    pos++;
  if ( _args.length() > 1 && _args[pos] != '#' ) {
    pr.response = "Invalid channel name\n";
    return pr;
  }
  std::string channelName = _args.substr( pos, _args.find(' ', pos) - pos );
  if ( !_channelManager->isOperator(channelName, _userFD) ) {
    pr.response = "You are not an operator\n";
    return pr;
  }
  pos = _args.find(' ', pos) + 1;
  while ( pos < _args.length() ) {
    char mode = _args[pos++];
    if ( mode == '+' || mode == '-' ) {
      add = ( mode == '+' );
      continue;
    }
    std::string target;
    if (((mode == 'k' || mode == 'l') && add) || mode == 'o' ) {
      pos++;
      size_t spacePos = _args.find(' ', pos);
      if (spacePos != std::string::npos) {
        target = _args.substr(pos, spacePos - pos);
        pos = spacePos + 1;
      } else {
        target = _args.substr(pos);
        pos = _args.length();
      }
    }
    Channel *channel = _channelManager->getChannel(channelName);
    if ( !channel ) {
      pr.response = "Channel does not exist\n";
      return pr;
    }
    switch ( mode ) {
      case 'k':
        if ( add )
          channel->setPassword(target);
        else
          channel->setPassword("");
        break;
      case 'l':
        if ( add )
          channel->setMaxUsers(std::atoi(target.c_str()));
        else
          channel->setMaxUsers(0);
        break;
      case 'o':
        if ( add )
          channel->addOperator(_userManager->getFdFromNick(target));
        else
          channel->removeOperator(_userManager->getFdFromNick(target));
        break;
      case 'i':
        channel->setInviteOnly(add);
        break;
      case 't':
        channel->setTopicProtected(add);
        break;
      default:
        pr.response = "Invalid mode\n";
        return pr;
    }
  }
  pr.response = genUserMsg(_userManager->getUser(_userFD), "MODE" + _args);
  return pr;
}
