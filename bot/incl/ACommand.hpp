#pragma once
#ifndef __ACOMMAND_HPP__
#define __ACOMMAND_HPP__

#include <iostream>
#include <map>

class ACommand {
 private:
  const std::string _name;

 protected:
  std::string    _usernick;
  std::string    _args;

 public:
  ACommand();
  ACommand( std::string name, std::string args, std::string nick );
  virtual ~ACommand();
  ACommand( ACommand const &src );
  ACommand &operator=( ACommand const &src );

  virtual std::string execute() const = 0;
};

#endif
