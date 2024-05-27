#pragma once
#ifndef __REPLYCOMMAND_HPP__
#define __REPLYCOMMAND_HPP__

#include <iostream>
#include <cmath>

#include "ACommand.hpp"

class ReplyCommand : public ACommand {
 private:
 public:
  ReplyCommand( BotManager *BotManager, std::string args, int fd );
  ~ReplyCommand();
  ReplyCommand( ReplyCommand const &src );
  ReplyCommand &operator=( ReplyCommand const &src );
  std::string  execute() const;
};

#endif
