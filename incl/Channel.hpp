#pragma once
#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <iostream>
#include <map>

#include "User.hpp"

class Channel {
 private:
  std::map<std::string, User> _users;
  User                       *_operators;

 public:
  Channel();
  ~Channel();
  Channel( Channel const &src );
  Channel &operator=( Channel const &src );

  User *getUser( std::string user );
};

#endif
