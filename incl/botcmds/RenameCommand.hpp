#pragma once
#ifndef __RENAMECOMMAND_HPP__
#define __RENAMECOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class RenameCommand : public ACommand {
 private:
 public:
  RenameCommand( Authenticator *authenticator, std::string args, int fd );
  ~RenameCommand();
  RenameCommand( RenameCommand const &src );
  RenameCommand &operator=( RenameCommand const &src );
  std::string  execute() const;
};

#endif
