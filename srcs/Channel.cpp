#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel( std::string name ) : _inviteOnly( false ), _topicProtected( false ), _maxUsers( 0 ) {
  _name = name;
}

Channel::~Channel() {
  _users.clear();
  _operators.clear();
  _invitees.clear();
}

Channel::Channel( Channel const &src ) {
  *this = src;
}

Channel &Channel::operator=( Channel const &src ) {
  if ( this == &src )
    return ( *this );
  _operators = src._operators;
  _users     = src._users;
  _invitees  = src._invitees;
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

bool Channel::isInvitee( int user ) {
  for ( std::vector<int>::iterator it = _invitees.begin(); it != _invitees.end(); it++ )
    if ( *it == user )
      return true;
  return false;
}

std::vector<int> Channel::getAllMembersSansUser( int user ) {
  std::vector<int> members;
  for ( int i = 0; i < (int)_operators.size(); i++ )
  {
    if (_operators[i] != user)
      members.push_back( _operators[i] );
  }
  for ( int i = 0; i < (int)_users.size(); i++ )
  {
    if (_users[i] != user)
      members.push_back( _users[i] );
  }
  return members;
}

std::vector<int> Channel::getAllUsers() {
  return _users;
}

std::vector<int> Channel::getAllOperators() {
  return _operators;
}

std::vector<int> Channel::getAllMembers() {
  std::vector<int> allUsersAndOps;
  for ( int i = 0; i < (int)_operators.size(); i++ )
    allUsersAndOps.push_back( _operators[i] );
  for ( int i = 0; i < (int)_users.size(); i++ )
    allUsersAndOps.push_back( _users[i] );
  return allUsersAndOps;
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

std::string Channel::getModes( void ) {
  std::string modes = "";
  if ( _inviteOnly )
    modes += "i";
  if ( _topicProtected )
    modes += "t";
  if ( _password != "" )
    modes += "k";
  if ( _maxUsers != 0 )
    modes += "l";
  return modes;
}

std::string Channel::getModeParams( void ) {
  std::string params = "";
  std::stringstream ss;
  if ( _password != "" )
    params += " " + _password;
  if ( _maxUsers != 0 ){
    ss << _maxUsers;
    params += " " + ss.str();
  }
  return params;
}

void Channel::addUser( int _userFD ) {
  if ( isUser( _userFD ) )
    return;
  _users.push_back( _userFD );
}

void Channel::addOperator( int _userFD ) {
  if ( isOperator( _userFD ) )
    return;
  _operators.push_back( _userFD );
}

void Channel::addInvitee( int _userFD ) {
  if ( isInvitee( _userFD ) )
    return;
  _invitees.push_back( _userFD );
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

void Channel::removeInvitee( int _userFD ) {
  std::vector<int>::iterator it = std::find( _invitees.begin(), _invitees.end(), _userFD );
  if ( it != _invitees.end() )
    _invitees.erase( it );
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
