#pragma once
#ifndef __INVITECOMMAND_HPP__
#define __INVITECOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class InviteCommand : public ACommand {
 private:
 public:
  InviteCommand( std::string args, std::string Invite );
  ~InviteCommand();
  InviteCommand( InviteCommand const &src );
  InviteCommand &operator=( InviteCommand const &src );
  std::string  execute() const;
};

#endif
