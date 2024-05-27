#pragma once
#ifndef __BOTMANAGER_HPP__
#define __BOTMANAGER_HPP__

#include <iostream>
#include <map>
#include <sstream>

#include "Bot.hpp"

class BotManager {
 private:
  BotManager( BotManager const& src );
  BotManager& operator=( BotManager const& src );
  
  std::map<std::string, Bot*> _bots;

 public:
  BotManager();
  ~BotManager();

  Bot* getBot( std::string &name);
  std::map<std::string, Bot*> getAllBots();
  void addBot( std::string &name, Bot* bot );
  void delBot( std::string name );
  void clearUserFromBots( int fd );
};

#endif
