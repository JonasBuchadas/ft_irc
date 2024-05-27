#pragma once
#ifndef __GRANTCOMMAND_HPP__
#define __GRANTCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class GrantCommand : public ACommand {
 private:
 public:
  GrantCommand( Authenticator *authenticator, std::string args, int fd );
  ~GrantCommand();
  GrantCommand( GrantCommand const &src );
  GrantCommand &operator=( GrantCommand const &src );
  std::string  execute() const;
};

#endif
