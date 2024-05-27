#pragma once
#ifndef __ACOMMAND_HPP__
#define __ACOMMAND_HPP__

#include <iostream>
#include <map>

#include "BotManager.hpp"

class ACommand {
 private:
  const std::string _name;

 protected:
  BotManager    *_BotManager;
  int            _userFD;
  std::string    _args;

 public:
  ACommand( BotManager *BotManager );
  ACommand( std::string name, BotManager *BotManager, std::string args, int fd );
  virtual ~ACommand();
  ACommand( ACommand const &src );
  ACommand &operator=( ACommand const &src );

  virtual std::string execute() const = 0;
};

#endif