#include "User.hpp"

User::User() {}

User::~User() {}

User::User( User const &src ) {
  *this = src;
}

User &User::operator=( User const &src ) {
  if ( this == &src )
    return ( *this );
  _serverName = src._serverName;
  _nickName   = src._nickName;
  return ( *this );
}

void User::join() {
  // TODO Implement me!!
}

void User::kick() {
  // TODO Implement me!!
}

void User::mode() {
  // TODO Implement me!!
}

void User::invite() {
  // TODO Implement me!!
}

void User::topic( std::string ) {
  // TODO Implement me!!
}
