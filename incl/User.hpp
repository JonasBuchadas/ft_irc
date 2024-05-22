#pragma once
#ifndef __USER_HPP__
#define __USER_HPP__

#include <iostream>

class User {
 private:
  User( User const &src );
  User       &operator=( User const &src );
  std::string _serverName;
  std::string _nickName;
  bool        _passOK;
  bool        _loggedIn;

 public:
  User();
  ~User();

  void setNick( std::string &nick );
  void setName( std::string &name );
  void setPassword( bool password );
  void setLoggedIn( bool loggedin );

  std::string getNick( void ) const;
  std::string getName( void ) const;
  bool getPassword( void ) const;
  bool getLoggedIn( void ) const;

  void join();
  void kick();
  void mode( char action );
  void invite();
  void topic( std::string );
};

#endif
