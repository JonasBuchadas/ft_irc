#pragma once
#ifndef __PRIVCOMMAND_HPP__
#define __PRIVCOMMAND_HPP__

#include <iostream>
#include <stdlib.h>
#include <arpa/inet.h>

#include "ACommand.hpp"

class PrivCommand : public ACommand {
 private:
 public:
  PrivCommand( Authenticator *authenticator, std::string args, int fd );
  ~PrivCommand();
  PrivCommand( PrivCommand const &src );
  PrivCommand  &operator=( PrivCommand const &src );
  std::string execute() const;
};

#endif
