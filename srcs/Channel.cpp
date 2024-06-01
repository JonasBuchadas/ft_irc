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

bool Channel::isUser( int user ) {
  for ( std::vector<int>::iterator it = _users.begin(); it != _users.end(); it++ )
    if ( *it == user )
      return true;
  return false;
}

bool Channel::isOperator( int user ) {
  for ( std::vector<int>::iterator it = _operators.begin(); it != _operators.end(); it++ )
    if ( *it == user )
      return true;
  return false;
}

std::vector<int> Channel::getAllUsers() {
  return _users;
}

std::vector<int> Channel::getAllOperators() {
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

void Channel::removeUser( int _userFD ) {
  std::vector<int>::iterator it = std::find( _users.begin(), _users.end(), _userFD );
  if ( it != _users.end() )
    _users.erase( it );
}

void Channel::removeOperator( int _userFD ) {
  std::vector<int>::iterator it = std::find( _operators.begin(), _operators.end(), _userFD );
  if ( it != _operators.end() )
    _operators.erase( it );
}

void Channel::setOperator( int user ) {
  _operators.push_back( user );
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
