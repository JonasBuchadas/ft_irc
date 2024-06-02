#pragma once
#ifndef __NAMESCOMMAND_HPP__
#define __NAMESCOMMAND_HPP__

#include <iostream>
#include <vector>
#include <cstdlib>

#include "ACommand.hpp"

class NamesCommand : public ACommand {
 private:
 public:
  NamesCommand( std::string args, std::string Names );
  ~NamesCommand();
  NamesCommand( NamesCommand const &src );
  NamesCommand &operator=( NamesCommand const &src );
  std::string  execute() const;
};

#endif
