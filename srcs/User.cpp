#include "User.hpp"

User::User() : _serverName(""), _nickName(""), _passOK(false), _loggedIn(false) {}

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

void User::setPassword( bool password ) {
  _passOK = password;
}

void User::setLoggedIn( bool loggedIn ) {
  _loggedIn = loggedIn;
}

void User::setIp( uint32_t ip ) {
  _ip = ip;
}

std::string User::getNick( void ) const {
  return _nickName;
}

std::string User::getName( void ) const {
  return _serverName;
}

bool User::getPassword( void ) const {
  return _passOK;
}

bool User::getLoggedIn( void ) const {
  return _loggedIn;
}

uint32_t User::getIp( void ) const {
  return _ip;
}
