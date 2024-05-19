#pragma once
#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include <iostream>
#include <functional>
#include <map>
#include <vector>

class User;
class Server;

class Commands {
 private:
  Commands( Commands const &src );
  Commands &operator=( Commands const &src );

  Server& _server;
  typedef std::string (Commands::*CommandFunction)( const std::string&, int fd );
  std::map<std::string, CommandFunction> _command;

  std::map<int, std::string>_passlist;
  std::map<int, std::string>_nicklist;
  std::map<int, std::string>_namelist;

 public:
  Commands(Server &server);
  ~Commands();

  std::string executeCommand(const std::string& command, const std::string& message, int fd);
  int authenticateUser( int fd );
  void releaseUserInfo( int fd );

  std::string checkPasswd( const std::string& message, int fd );
  std::string setNickname( const std::string& message, int fd );
  std::string setUsername( const std::string& message, int fd );
  std::string joinChannel( const std::string& message, int fd );
  std::string partChannel( const std::string& message, int fd );
  std::string changeModes( const std::string& message, int fd );
  std::string kickoutUser( const std::string& message, int fd );
  std::string changeTopic( const std::string& message, int fd );
  std::string inviteUser( const std::string& message, int fd );
  std::string directMsg( const std::string& message, int fd );
};

#endif
