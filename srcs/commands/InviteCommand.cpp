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
  PreparedResponse pr = PreparedResponse();

  if ( !_userManager->isLoggedIn( _userFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_NOTREGISTERED, "INVITE");
    return pr;
  }

  std::stringstream ss( _args );
  std::string       inviteeNick;
  std::string       channelName;
  std::string       invalidArg;
  ss >> inviteeNick;
  ss >> channelName;
  ss >> invalidArg;

  if ( inviteeNick.empty() || channelName.empty() || !invalidArg.empty() ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_NEEDMOREPARAMS, "INVITE");
    return pr;
  }

  if ( !_userManager->nickNameExists( _userFD, inviteeNick ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_NOSUCHNICK, channelName);
    return pr;
  }

  int inviteeFD = _userManager->getFdFromNick( inviteeNick );
  if ( !_userManager->isLoggedIn( inviteeFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_TARGETNOTAUTH, "");
    return pr;
  }

  if ( !_channelManager->channelExists( channelName ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_NOSUCHCHANNEL, "INVITE");
    return pr;
  }

  if ( !_channelManager->getChannel( channelName )->isUser( _userFD ) &&
       !_channelManager->getChannel( channelName )->isOperator( _userFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_USERNOTINCHANNEL, "INVITE");
    return pr;
  }

  if ( _channelManager->getChannel( channelName )->isUser( inviteeFD ) ||
       _channelManager->getChannel( channelName )->isOperator( inviteeFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_USERONCHANNEL, _userManager->getNick( _userFD ));
    return pr;
  }

  if ( _channelManager->getChannel( channelName )->isInvitee( inviteeFD ) ) {
    pr.recipients.push_back( _userFD );
    pr.response = genServerMsg(ERR_TARGETALREADYINV, "");
    return pr;
  }

  _channelManager->getChannel( channelName )->addInvitee( inviteeFD );

  pr.recipients.push_back( inviteeFD );
  pr.response = genUserMsg( _userManager->getUser( _userFD ), "INVITE" + _args );
  return pr;
}
