#include "User.hpp"

User::User( void ) {}

User::User( std::string serverName, std::string nickName ) : _serverName( serverName ), _nickName( nickName ) {}

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

void User::setNick( std::string &nick ) {
  _nickName = nick;
}

void User::setName( std::string &name ) {
  _serverName = name;
}

void User::setPassword( std::string &password ) {
  _password = password;
}

std::string User::getNick( void ) const {
  return _nickName;
}

std::string User::getName( void ) const {
  return _serverName;
}

std::string User::getPassword( void ) const {
  return _password;
}

void User::join() {
  // TODO Implement me!!
}

void User::kick() {
  // TODO Implement me!!
}

void User::mode( char action ) {
  (void)action;
  // TODO Implement me!!
}

void User::invite() {
  // TODO Implement me!!
}

void User::topic( std::string ) {
  // TODO Implement me!!
}
