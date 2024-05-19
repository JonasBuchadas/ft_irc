#pragma once
#ifndef __AUTHENTICATOR_HPP__
#define __AUTHENTICATOR_HPP__

#include <iostream>
#include <map>
#include <vector>

class Authenticator {
 private:
  Authenticator( Authenticator const &src );
  Authenticator &operator=( Authenticator const &src );

  std::map<int, std::string>_passlist;
  std::map<int, std::string>_nicklist;
  std::map<int, std::string>_namelist;
  typedef std::string (Authenticator::*CommandFunction)( const std::string&, int fd );
  std::map<std::string, CommandFunction> _command;

  std::string checkPasswd( const std::string& message, int fd );
  std::string setNickname( const std::string& message, int fd );
  std::string setUsername( const std::string& message, int fd );

 public:
  Authenticator();
  ~Authenticator();

  std::string executeCommand(const std::string& command, const std::string& message, int fd);

  std::string getPass(int fd);
  std::string getNick(int fd);
  std::string getUser(int fd);

  int authenticateUser( std::string password, int fd );
  void releaseUserInfo( int fd );

};

#endif
