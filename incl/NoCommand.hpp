#pragma once
#ifndef __NOCOMMAND_HPP__
#define __NOCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class NoCommand : public ACommand {
 private:
 public:
  NoCommand( Authenticator *authenticator, std::string args, int fd );
  ~NoCommand();
  NoCommand( NoCommand const &src );
  NoCommand  &operator=( NoCommand const &src );
  std::string execute() const;
};

#endif
