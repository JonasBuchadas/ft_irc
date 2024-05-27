#include "CommandFactory.hpp"

CommandFactory::CommandFactory() {}

CommandFactory::~CommandFactory() {
}

CommandFactory::CommandFactory( CommandFactory const &src ) {
  *this = src;
}

CommandFactory &CommandFactory::operator=( CommandFactory const &src ) {
  if ( this == &src )
    return ( *this );
  return ( *this );
}

ACommand *makeUserCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new UserCommand( authenticator, args, fd );
}

ACommand *makePassCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new PassCommand( authenticator, args, fd );
}

ACommand *makeNickCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new NickCommand( authenticator, args, fd );
}

ACommand *makePrivCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new PrivCommand( authenticator, args, fd );
}

// BOT BONUS
ACommand *makeCallCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new CallCommand( authenticator, args, fd );
}

ACommand *makeDismissCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new DismissCommand( authenticator, args, fd );
}

ACommand *makeRenameCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new RenameCommand( authenticator, args, fd );
}

ACommand *makeGrantCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new GrantCommand( authenticator, args, fd );
}

ACommand *makeRevokeCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new RevokeCommand( authenticator, args, fd );
}

ACommand *makeAliasCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new AliasCommand( authenticator, args, fd );
}

ACommand *makeRmidCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new RmidCommand( authenticator, args, fd );
}

ACommand *makeOpenCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new OpenCommand( authenticator, args, fd );
}

ACommand *makeCloseCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new CloseCommand( authenticator, args, fd );
}

ACommand *makeViewCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new ViewCommand( authenticator, args, fd );
}

ACommand *makeReplyCommand( Authenticator *authenticator, std::string args, int fd ) {
  return new ReplyCommand( authenticator, args, fd );
}



ACommand *CommandFactory::makeCommand( std::string commandName, Authenticator *authenticator, std::string args, int fd ) {
  const std::string enumCommand[] = { "USER", "PASS", "NICK", "PRIVMSG" };
  const funcPtr     enumFunc[]    = {
      &makeUserCommand,
      &makePassCommand,
      &makeNickCommand,
      &makePrivCommand,
  };
  for ( int i = 0; i < 4; i++ ) {
    if ( commandName == enumCommand[i] ) {
      ACommand *c = ( enumFunc[i]( authenticator, args, fd ) );
      return c;
    }
  }

  // BOT BONUS
  const std::string enumBotCmd[]  = { "CALL", "DISMISS", "RENAME", "GRANT", \
      "REVOKE", "ALIAS", "RMID", "OPEN", "CLOSE", "VIEW", "REPLY"  };
  const funcPtr     enumBotFunc[] = {
      &makeCallCommand,
      &makeDismissCommand,
      &makeRenameCommand,
      &makeGrantCommand,
      &makeRevokeCommand,
      &makeAliasCommand,
      &makeRmidCommand,
      &makeOpenCommand,
      &makeCloseCommand,
      &makeViewCommand,
      &makeReplyCommand,
  };
  for ( int i = 0; i < 11; i++ ) {
    if ( commandName == enumBotCmd[i] ) {
      ACommand *c = ( enumBotFunc[i]( authenticator, args, fd ) );
      return c;
    }
  }
  return new NoCommand( authenticator, args, fd );
}
