#pragma once
#ifndef __USERMANAGER_HPP__
#define __USERMANAGER_HPP__

#include <arpa/inet.h>

#include <iostream>
#include <map>
#include <vector>

#include "User.hpp"

class UserManager {
 private:
  UserManager();
  std::map<int, User*> _users;
  const char*          _password;

  typedef std::string ( UserManager::*CommandFunction )( const std::string&, int fd );
  std::map<std::string, CommandFunction> _command;

  // std::string checkPasswd( const std::string& message, int fd );
  // std::string setNickname( const std::string& message, int fd );
  // std::string setUsername( const std::string& message, int fd );

 public:
  UserManager( UserManager const& src );
  UserManager& operator=( UserManager const& src );
  UserManager( const char* password );
  ~UserManager();

  // std::string executeCommand( const std::string& command, const std::string& message, int fd );

  User*                getUser( int fd );
  bool                 getPass( int fd );
  std::string          getNick( int fd );
  bool                 isLoggedIn( int fd );
  std::string          getServerPass();
  std::string          getUserName( int fd );
  std::map<int, User*> getAllUsers();
  void                 addUser( int fd, User* user );
  bool                 userNameExists( int fd, std::string userName );
  bool                 nickNameExists( int fd, std::string nickName );

  bool isValidArg( std::string str );
  int  getFdFromNick( std::string str );

  bool authenticateUser( int fd );
  void setUserIp( int fd );
  void releaseUserInfo( int fd );
  void clearUsers( void );
};

#endif
