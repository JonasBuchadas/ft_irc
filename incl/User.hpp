#pragma once
#ifndef __USER_HPP__
#define __USER_HPP__

#include <iostream>

class User {
 private:
  User( User const &src );
  User &operator=( User const &src );

 public:
  User(std::string serverName, std::string nickName);
  ~User();
  
  std::string _serverName;
  std::string _nickName;

  void join();
  void kick();
  void mode( char action );
  void invite();
  void topic( std::string );
};

#endif
