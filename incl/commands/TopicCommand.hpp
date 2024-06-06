#pragma once
#ifndef __TOPICCOMMAND_HPP__
#define __TOPICCOMMAND_HPP__

#include <iostream>

#include "ACommand.hpp"

class TopicCommand : public ACommand {
 private:
 public:
  TopicCommand( UserManager *userManager, ChannelManager *channelManager, std::string args, int fd );
  ~TopicCommand();
  TopicCommand( TopicCommand const &src );
  TopicCommand     &operator=( TopicCommand const &src );
  PreparedResponse execute() const;
};

#endif
