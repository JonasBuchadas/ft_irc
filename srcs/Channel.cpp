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

bool Channel::isUser( std::string user ) {
  for ( int j = 0; j < (int)_users.size(); j++ )
      if ( _users[j] == user )
        return 1;
  return 0;
}

bool Channel::isOperator( std::string user ) {
   for ( int j = 0; j < (int)_operators.size(); j++ )
      if ( (*_operators[j]) == user )
        return 1;
  return 0;
}

std::vector<std::string> Channel::getAllUsers() {
  return _users;
}

std::vector<std::string *> Channel::getAllOperators() {
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

void Channel::setOperator( std::string *user ) {
  _operators[(int)_operators.size()] = user;
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