#pragma once
#ifndef __USER_HPP__
#define __USER_HPP__

#include <iostream>
#include <arpa/inet.h>

class User {
 private:
  User( User const &src );
  User       &operator=( User const &src );
  std::string _serverName;
  std::string _nickName;
  uint32_t    _ip;
  bool        _passOK;
  bool        _loggedIn;

 public:
  User();
  ~User();

  void setNick( std::string &nick );
  void setName( std::string &name );
  void setPassword( bool password );
  void setLoggedIn( bool loggedin );
  void setIp( uint32_t ip );

  std::string getNick( void ) const;
  std::string getName( void ) const;
  bool getPassword( void ) const;
  bool getLoggedIn( void ) const;
  uint32_t getIp( void ) const;

  void join();
  void kick();
  void mode( char action );
  void invite();
  void topic( std::string );
};

#endif
