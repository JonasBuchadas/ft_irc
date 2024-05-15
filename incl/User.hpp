#pragma once
#ifndef __USER_HPP__
#define __USER_HPP__

#include <iostream>

class User {
 private:
  User( User const &src );
  User &operator=( User const &src );
  std::string _serverName;
  std::string _nickName;

 public:
  User(std::string serverName, std::string nickName);
  ~User();

  void setNick(std::string &nick);
  void setName(std::string &name);
  std::string getNick(void) const;
  std::string getName(void) const;


  void join();
  void kick();
  void mode( char action );
  void invite();
  void topic( std::string );
};

#endif
