#pragma once
#ifndef __USER_HPP__
#define __USER_HPP__

#include <iostream>

class User {
 private:
  std::string _serverName;
  std::string _nickName;

 public:
  User();
  ~User();
  User( User const &src );
  User &operator=( User const &src );

  void join();
  void kick();
  void mode( char action );
  void invite();
  void topic( std::string );
};

#endif
