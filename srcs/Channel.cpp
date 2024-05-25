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