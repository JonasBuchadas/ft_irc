#pragma once
#ifndef __CALLCOMMAND_HPP__
#define __CALLCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class CallCommand : public ACommand {
 private:
 public:
  CallCommand( Authenticator *authenticator, std::string args, int fd );
  ~CallCommand();
  CallCommand( CallCommand const &src );
  CallCommand &operator=( CallCommand const &src );
  std::string  execute() const;
};

#endif
