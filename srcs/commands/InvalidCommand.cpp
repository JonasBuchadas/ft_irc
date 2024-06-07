#include "commands/InvalidCommand.hpp"

InvalidCommand::InvalidCommand( UserManager *userManager, ChannelManager *channelManager,
                                std::string args, int fd ) : ACommand( "INVALID", userManager, channelManager, args, fd ) {}

InvalidCommand::~InvalidCommand() {
}

InvalidCommand::InvalidCommand( InvalidCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

InvalidCommand &InvalidCommand::operator=( InvalidCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse InvalidCommand::execute() const {
  std::stringstream argsStream( _args );
  std::string       InvalidCommandName;
  argsStream >> InvalidCommandName;
  return serverResponse( ERR_UNKNOWNCOMMAND, InvalidCommandName );
}
