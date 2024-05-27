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

ACommand *makeUserCommand( BotManager *BotManager, std::string args, int fd ) {
  return new UserCommand( BotManager, args, fd );
}

ACommand *makePassCommand( BotManager *BotManager, std::string args, int fd ) {
  return new PassCommand( BotManager, args, fd );
}

ACommand *makeNickCommand( BotManager *BotManager, std::string args, int fd ) {
  return new NickCommand( BotManager, args, fd );
}

ACommand *makePrivCommand( BotManager *BotManager, std::string args, int fd ) {
  return new PrivCommand( BotManager, args, fd );
}

// BOT BONUS
ACommand *makeCallCommand( BotManager *BotManager, std::string args, int fd ) {
  return new CallCommand( BotManager, args, fd );
}

ACommand *makeDismissCommand( BotManager *BotManager, std::string args, int fd ) {
  return new DismissCommand( BotManager, args, fd );
}

ACommand *makeRenameCommand( BotManager *BotManager, std::string args, int fd ) {
  return new RenameCommand( BotManager, args, fd );
}

ACommand *makeGrantCommand( BotManager *BotManager, std::string args, int fd ) {
  return new GrantCommand( BotManager, args, fd );
}

ACommand *makeRevokeCommand( BotManager *BotManager, std::string args, int fd ) {
  return new RevokeCommand( BotManager, args, fd );
}

ACommand *makeAliasCommand( BotManager *BotManager, std::string args, int fd ) {
  return new AliasCommand( BotManager, args, fd );
}

ACommand *makeRmidCommand( BotManager *BotManager, std::string args, int fd ) {
  return new RmidCommand( BotManager, args, fd );
}

ACommand *makeOpenCommand( BotManager *BotManager, std::string args, int fd ) {
  return new OpenCommand( BotManager, args, fd );
}

ACommand *makeCloseCommand( BotManager *BotManager, std::string args, int fd ) {
  return new CloseCommand( BotManager, args, fd );
}

ACommand *makeViewCommand( BotManager *BotManager, std::string args, int fd ) {
  return new ViewCommand( BotManager, args, fd );
}

ACommand *makeReplyCommand( BotManager *BotManager, std::string args, int fd ) {
  return new ReplyCommand( BotManager, args, fd );
}



ACommand *CommandFactory::makeCommand( std::string commandName, BotManager *BotManager, std::string args, int fd ) {
  const std::string enumCommand[] = { "USER", "PASS", "NICK", "PRIVMSG" };
  const funcPtr     enumFunc[]    = {
      &makeUserCommand,
      &makePassCommand,
      &makeNickCommand,
      &makePrivCommand,
  };
  for ( int i = 0; i < 4; i++ ) {
    if ( commandName == enumCommand[i] ) {
      ACommand *c = ( enumFunc[i]( BotManager, args, fd ) );
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
      ACommand *c = ( enumBotFunc[i]( BotManager, args, fd ) );
      return c;
    }
  }
  return new NoCommand( BotManager, args, fd );
}
