#include "commands/TopicCommand.hpp"

TopicCommand::TopicCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "TOPIC", userManager, channelManager, args, fd ) {}

TopicCommand::~TopicCommand() {
}

TopicCommand::TopicCommand( TopicCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

TopicCommand &TopicCommand::operator=( TopicCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse TopicCommand::execute() const {
  PreparedResponse pr = PreparedResponse();
  if ( !_userManager->isLoggedIn( _userFD ) )
    return serverResponse( ERR_NOTREGISTERED, "TOPIC" );

  std::stringstream argsStream( _args );
  std::string       channelName, topic;
  argsStream >> channelName >> topic;

  if ( channelName.empty() )
    return serverResponse( ERR_NEEDMOREPARAMS, "TOPIC" );

  if ( channelName[0] != '#' || !_channelManager->channelExists( channelName ) )
    return serverResponse( ERR_NOSUCHCHANNEL, channelName );

  if ( !_channelManager->getChannel( channelName )->isUser( _userFD ) \
  && !_channelManager->getChannel( channelName )->isOperator( _userFD ) )
    return serverResponse( ERR_USERNOTINCHANNEL, channelName );

  std::string t = _args.substr(_args.find("#") + channelName.length());
  if (!topic.empty() && t.find(":") != std::string::npos)
  {
    std::string extra = t.substr(0, t.find(":"));
    std::stringstream extraStream( extra );
    std::string excess;
    extraStream >> excess;
    if (!excess.empty())
      return serverResponse( ERR_NEEDMOREPARAMS, "TOPIC" );
    size_t topicProtected = _channelManager->getChannel( channelName )->getModes().find("t");
    if ( _channelManager->getChannel( channelName )->isOperator( _userFD ) \
    || (topicProtected == std::string::npos && _channelManager->getChannel( channelName )->isUser( _userFD )))
      _channelManager->getChannel( channelName )->setTopic( t.substr( t.find(":") + 1 ) );
    else
      return serverResponse( ERR_CHANOPRIVSNEEDED, "TOPIC" );
  }
  else if ( topic.empty() && t.find(":") == std::string::npos  && \
   _channelManager->getChannel( channelName )->getTopic().size() == 0)
    return serverResponse( RPL_NOTOPIC, channelName );
  else if ( topic.empty() && t.find(":") == std::string::npos  && \
   _channelManager->getChannel( channelName )->getTopic().size() > 0)
    return serverResponse( RPL_TOPIC, channelName + " :" + _channelManager->getChannel( channelName )->getTopic() );
  else
    return serverResponse( ERR_NEEDMOREPARAMS, "TOPIC" );

  pr.allresponses[genUserMsg( _userManager->getUser( _userFD ), "TOPIC " + channelName + \
  " " + _channelManager->getChannel( channelName )->getTopic())] \
   = _channelManager->getChannel( channelName)->getAllMembers();
  return pr;
}
