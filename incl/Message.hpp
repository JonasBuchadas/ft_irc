#pragma once
#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <iostream>

#include "Channel.hpp"
#include "User.hpp"

class Message {
 private:
  User        _author;
  Channel     _channel;
  char       *_timestamp;
  std::string _msg;

 public:
  Message();
  ~Message();
  Message( Message const &src );
  Message &operator=( Message const &src );
};

#endif
