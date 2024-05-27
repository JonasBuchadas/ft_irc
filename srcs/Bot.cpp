#include "Bot.hpp"

Bot::Bot() {
  _operators.clear();
  _users.clear();
  _aliases.clear();
  _isOpen.clear();
}

Bot::~Bot() {}

Bot::Bot( Bot const &src ) {
  *this = src;
}

Bot &Bot::operator=( Bot const &src ) {
  if ( this == &src )
    return ( *this );
  _name      = src._name;
  _operators = src._operators;
  _users     = src._users;
  _aliases   = src._aliases;
  _isOpen    = src._isOpen;
  return ( *this );
}

std::string Bot::getName( void ) const {
  return _name;
}

bool Bot::getIsOpen( std::string id ) {
  return _isOpen[id];
}

std::vector<int> Bot::getAllOpers() {
  return _operators;
}

std::vector<int> Bot::getAllUsers() {
  return _users;
}

std::map<std::string, std::map<int, std::string> > Bot::getAllAlias() {
  return _aliases;
}

int Bot::getOper( int fd ) {
  for ( int j = 0; j < (int)_operators.size(); j++ ) {
      if ( _operators[j] == fd )
        return _operators[j];
  }
  return -1;
}

int Bot::getUser( int fd ) {
  for ( int j = 0; j < (int)_users.size(); j++ ) {
      if ( _users[j] == fd )
        return _users[j];
  }
  return -1;
}

int Bot::getAlias( std::string id ) {
  if ( _aliases[id].size() > 0 )
    return _aliases[id].size();
  return 0;
}

std::string Bot::getOption( std::string alias, int option )
{
  if ( _aliases[alias][option].size() > 0 )
    return _aliases[alias][option];
  return NULL;
}

void Bot::setName( std::string &name ) {
  _name = name;
}

void Bot::addOper( int fd ) {
  _operators.push_back( fd );
}

void Bot::addUser( int fd ) {
  _users.push_back( fd );
}

void Bot::rmvOper( int fd ) {
  std::vector<int>::iterator it = _operators.begin();
  for ( int j = 0; j < (int)_operators.size(); j++ ) {
    if ( _operators[j] == fd )
    {
      _operators.erase(it);
      break ;
    }
    it++;
  }
}

void Bot::rmvUser( int fd ) {
  std::vector<int>::iterator it = _users.begin();
  for ( int j = 0; j < (int)_users.size(); j++ ) {
    if ( _users[j] == fd )
    {
      _users.erase(it);
      break ;
    }
    it++;
  }
}

void Bot::setIsOpen( std::string id, bool open ) {
  _isOpen[id] = open;
}

void Bot::setAlias( std::string id, std::string msg ) {
  int next = _aliases[id].size();
  _aliases[id][next] = msg;
}

void Bot::rmAlias( std::string id, int num ) {
  if (num != -1)
  {
    _aliases[id].clear();
    _aliases[id].erase( num );
  }
  else
  {
    for (int i = 0; i < (int)_aliases[id].size(); i++)
    {
      _aliases[id].clear();
      _aliases[id].erase( i );
    }
    _aliases[id].clear();
    _aliases.erase( id );
  }
}