#include "Channel.hpp"

Channel::Channel() {}

Channel::~Channel() {
  _users.clear();
}

Channel::Channel( Channel const &src ) {
  *this = src;
}

Channel &Channel::operator=( Channel const &src ) {
  if ( this == &src )
    return ( *this );
  _operators = src._operators;
  _users     = src._users;
  return ( *this );
}

User *Channel::getUser( std::string user ) {
  if ( _users.find( user ) != _users.end() )
    return &_users[user];
  return NULL;
}

User *Channel::getOperator( void ) {
  return _operators;
}

bool Channel::isInviteOnly( void ) {
  return _inviteOnly;
}

bool Channel::isTopicProtected( void ) {
  return _topicProtected;
}

std::string Channel::getTopic( void ) {
  return _topic;
}

std::string Channel::getName( void ) {
  return _name;
}

std::string Channel::getPassword( void ) {
  return _password;
}

unsigned int Channel::getMaxUsers( void ) {
  return _maxUsers;
}

void Channel::setOperator( User *user ) {  // Placeholder function
  _operators = user;
}

void Channel::setInviteOnly( bool inviteOnly ) {
  _inviteOnly = inviteOnly;
}

void Channel::setTopicProtected( bool topicProtected ) {
  _topicProtected = topicProtected;
}

void Channel::setTopic( std::string topic ) {
  _topic = topic;
}

void Channel::setPassword( std::string password ) {
  _password = password;
}

void Channel::setMaxUsers( unsigned int maxUsers ) {
  _maxUsers = maxUsers;
}