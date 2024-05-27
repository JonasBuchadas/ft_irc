#include "Authenticator.hpp"

Authenticator::Authenticator( const char* password ) : _password( password ) {
  _users.clear();
  _command.clear();
}

Authenticator::~Authenticator() {
  clearUsers();
}

Authenticator::Authenticator( Authenticator const& src ) {
  *this = src;
}

Authenticator& Authenticator::operator=( Authenticator const& src ) {
  if ( this == &src )
    return ( *this );
  _users = src._users;
  return ( *this );
}

bool Authenticator::isValidArg( std::string str ) {
  for ( size_t i = 0; i < str.length(); i++ )
    if ( !isdigit( str[i] ) && !isalpha( str[i] ) )
      return 0;
  return 1;
}

bool Authenticator::userNameExists( int fd, std::string userName ) {
  for ( std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++ ) {
    if ( it->first != fd && it->second->getName() == userName )
      return true;
  }
  return false;
}

bool Authenticator::nickNameExists( int fd, std::string nickName ) {
  for ( std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++ ) {
    if ( it->first != fd && it->second->getNick() == nickName )
      return true;
  }
  return false;
}

bool Authenticator::getPass( int fd ) {
  return _users[fd]->getPassword();
}

std::string Authenticator::getNick( int fd ) {
  return _users[fd]->getNick();
}

User* Authenticator::getUser( int fd ) {
  std::map<int, User*>::iterator it = _users.find( fd );
  if ( it == _users.end() )
    return NULL;
  return it->second;
}

std::string Authenticator::getServerPass() {
  return _password;
}

std::map<int, User*> Authenticator::getAllUsers() {
  return _users;
}

void Authenticator::addUser( int fd, User* user ) {
  _users[fd] = user;
}

bool Authenticator::authenticateUser( int fd ) {
  if ( _users[fd] && !_users[fd]->getLoggedIn() && _users[fd]->getPassword() && !_users[fd]->getNick().empty() && !_users[fd]->getName().empty() ) {
    _users[fd]->setLoggedIn( true );
    return true;
  }
  return false;
}

void Authenticator::releaseUserInfo( int fd ) {
  if ( _users.find( fd ) != _users.end() ) {
    delete _users[fd];
    _users.erase( fd );
  }
}

void Authenticator::clearUsers() {
  std::map<int, User*>::iterator it;
  for ( it = _users.begin(); it != _users.end(); it++ ) {
    delete it->second;
    it->second = NULL;
  }
  _users.clear();
}
