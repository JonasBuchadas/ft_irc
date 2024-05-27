#include "BotManager.hpp"

BotManager::BotManager() {
  _bots.clear();
}

BotManager::~BotManager() {
  std::map<std::string, Bot*>::iterator it = _bots.begin();
  for ( it == _bots.begin(); it != _bots.end(); it++ )
  {
    delete it->second;
    it->second = NULL;
  }
  _bots.clear();
}

BotManager::BotManager( BotManager const& src ) {
  *this = src;
}

BotManager& BotManager::operator=( BotManager const& src ) {
  if ( this == &src )
    return ( *this );
  _bots = src._bots;
  return ( *this );
}

Bot* BotManager::getBot( std::string &name)
{
  std::map<std::string, Bot*>::iterator it = _bots.begin();
  for ( ; it != _bots.end(); it++ )
  {
    if (it->second && it->second->getName() == name)
      return it->second;
  }
  return NULL;
}

void BotManager::addBot( std::string &name, Bot* bot )
{
  _bots[name] = bot;
}

void BotManager::delBot( std::string name ) {
  delete _bots[name];
  _bots.erase( name );
}

std::map<std::string, Bot*> BotManager::getAllBots()
{
  return _bots;
}

void BotManager::clearUserFromBots( int fd ) {
  std::map<std::string, Bot*>::iterator it = _bots.begin();
  for ( ; it != _bots.end(); it++ )
  {
    if (it->second && it->second->getOper( fd ) != -1 )
      it->second->rmvOper( fd );
    if (it->second && it->second->getUser( fd ) != -1 )
      it->second->rmvUser( fd );
    if (it->second && it->second->getAllOpers().empty() )
    {
      delete _bots[it->first];
      _bots.erase( it->first );
    }
  }
}
