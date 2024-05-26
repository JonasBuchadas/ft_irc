#pragma once
#ifndef __PASSCOMMAND_HPP__
#define __PASSCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class PassCommand : public ACommand {
 private:
 public:
  PassCommand( Authenticator *authenticator, std::string args, int fd );
  ~PassCommand();
  PassCommand( PassCommand const &src );
  PassCommand     &operator=( PassCommand const &src );
  PreparedResponse execute() const;
};

#endif
