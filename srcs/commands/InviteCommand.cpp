#include "commands/InviteCommand.hpp"

InviteCommand::InviteCommand( UserManager *userManager, ChannelManager *channelManager,
                              std::string args, int fd ) : ACommand( "INVITE", userManager, channelManager, args, fd ) {}

InviteCommand::~InviteCommand() {
}

InviteCommand::InviteCommand( InviteCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

InviteCommand &InviteCommand::operator=( InviteCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse InviteCommand::execute() const {
  if ( !_userManager->isLoggedIn( _userFD ) )
    return serverResponse( ERR_NOTREGISTERED, "INVITE" );

  std::stringstream argsStream( _args );
  std::string       inviteeNick, channelName, invalidArg;
  argsStream >> inviteeNick >> channelName >> invalidArg;

  if ( inviteeNick.empty() || channelName.empty() || !invalidArg.empty() )
    return serverResponse( ERR_NEEDMOREPARAMS, "INVITE" );

  if ( !_userManager->nickNameExists( inviteeNick ) )
    return serverResponse( ERR_NOSUCHNICK, channelName );

  int inviteeFD = _userManager->getFdFromNick( inviteeNick );
  if ( !_userManager->isLoggedIn( inviteeFD ) )
    return serverResponse( ERR_TARGETNOTAUTH, "" );

  if ( !_channelManager->channelExists( channelName ) )
    return serverResponse( ERR_NOSUCHCHANNEL, "INVITE" );

  if ( !_channelManager->getChannel( channelName )->isUser( _userFD ) &&
       !_channelManager->getChannel( channelName )->isOperator( _userFD ) )
    return serverResponse( ERR_USERNOTINCHANNEL, channelName );

  if ( _channelManager->getChannel( channelName )->isUser( inviteeFD ) ||
       _channelManager->getChannel( channelName )->isOperator( inviteeFD ) )
    return serverResponse( ERR_USERONCHANNEL, _userManager->getNick( inviteeFD ) );

  if ( _channelManager->getChannel( channelName )->isInvitee( inviteeFD ) )
    return serverResponse( ERR_TARGETALREADYINV, "" );

  _channelManager->getChannel( channelName )->addInvitee( inviteeFD );
  PreparedResponse pr = PreparedResponse();
  pr.recipients.push_back( inviteeFD );
  pr.response = genUserMsg( _userManager->getUser( _userFD ), "INVITE" + _args );
  return pr;
}
