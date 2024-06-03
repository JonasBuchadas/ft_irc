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
  

  while ( pos < _args.length() ) {
    char mode = _args[pos++];
    if ( mode == '+' || mode == '-' ) {
      add = ( mode == '+' );
      continue;
    }
    std::string target;
    if (mode == 'k' || mode == 'l' || mode == 'o' ) {
      size_t spacePos = _args.find(' ', pos);
      if (spacePos != std::string::npos) {
        target = _args.substr(pos, spacePos - pos);
        pos = spacePos + 1;
      } else {
        target = _args.substr(pos);
        pos = _args.length();
      }
    }
    
  }
  // TODO: Implement me!
  return PreparedResponse();
}
