#pragma once
#ifndef __ACOMMAND_HPP__
#define __ACOMMAND_HPP__

#include <iostream>
#include <map>

#include "Authenticator.hpp"

class ACommand {
 private:
  const std::string _name;

 protected:
  Authenticator &_authenticator;
  int            _userFD;
  std::string    _args;

 public:
  ACommand( Authenticator authenticator );
  ACommand( std::string name, Authenticator &authenticator, std::string args, int fd );
  virtual ~ACommand();
  ACommand( ACommand const &src );
  ACommand &operator=( ACommand const &src );

  virtual std::string execute() const = 0;
};

#endif
