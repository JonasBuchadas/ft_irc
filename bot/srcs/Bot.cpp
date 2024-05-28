#include "Bot.hpp"

Bot::Bot() {
  _users.clear();
  _asks.clear();
  _isOpen.clear();
}

Bot::~Bot() {}

Bot::Bot( Bot const &src ) {
  *this = src;
}

Bot &Bot::operator=( Bot const &src ) {
  if ( this == &src )
    return ( *this );
  _users  = src._users;
  _asks   = src._asks;
  _isOpen = src._isOpen;
  return ( *this );
}

bool Bot::getIsOpen( std::string id ) {
  return _isOpen[id];
}

std::vector<std::string> Bot::getAllUsers() {
  return _users;
}

std::map<std::string, std::map<int, std::string> > Bot::getAllAsk() {
  return _asks;
}

std::string Bot::getUser( std::string nick ) {
  for ( int j = 0; j < (int)_users.size(); j++ ) {
      if ( _users[j] == nick )
        return _users[j];
  }
  return "";
}

int Bot::getAsk( std::string id ) {
  if ( _asks[id].size() > 0 )
    return _asks[id].size();
  return 0;
}

std::string Bot::getOption( std::string ask, int option )
{
  if ( _asks[ask][option].size() > 0 )
    return _asks[ask][option];
  return NULL;
}

void Bot::addUser( std::string nick ) {
  _users.push_back( nick );
}

void Bot::rmvUser( std::string nick ) {
  std::vector<std::string>::iterator it = _users.begin();
  for ( int j = 0; j < (int)_users.size(); j++ ) {
    if ( _users[j] == nick )
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

void Bot::setAsk( std::string id, std::string msg ) {
  int next = _asks[id].size();
  _asks[id][next] = msg;
}

void Bot::rmAsk( std::string id, int num ) {
  if (num != -1)
  {
    _asks[id].clear();
    _asks[id].erase( num );
  }
  else
  {
    for (int i = 0; i < (int)_asks[id].size(); i++)
    {
      _asks[id].clear();
      _asks[id].erase( i );
    }
    _asks[id].clear();
    _asks.erase( id );
  }
}