#pragma once
#ifndef __SHOOTCOMMAND_HPP__
#define __SHOOTCOMMAND_HPP__

#include <iostream>
#include <vector>
#include <cstdlib>

#include "ACommand.hpp"

class ShootCommand : public ACommand {
 private:
 public:
  ShootCommand( std::string args, std::string nick );
  ~ShootCommand();
  ShootCommand( ShootCommand const &src );
  ShootCommand &operator=( ShootCommand const &src );
  std::string  execute() const;
};

#endif
