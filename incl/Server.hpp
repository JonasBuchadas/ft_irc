#pragma once
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <map>
#include <vector>

#include "Connector.hpp"

class Connector;

#define BACKLOG 10

class Server {
 private:
  const char           *_port;
  std::string           _password;
  int                   _listeningSocket;
  int                   _fdSize;
  Connector             _connector;

  /*
  std::map<int, User *> _users;
  std::vector<int>      _recipients;
  Authenticator         _authenticator;
  
  typedef std::string (Server::*CommandFunction)( const std::string&, int fd );
  std::map<std::string, CommandFunction> _command;
  */

  Server();
  Server &operator=( Server const &src );

  void setPort( const char *port ) throw( std::exception );
  void setPassword( char const *password ) throw( std::exception );
  void setupListeningSocket( void ) throw( std::exception );


  /*
  std::string executeCommand(const std::string& command, const std::string& message, int fd);
  std::string joinChannel( const std::string& message, int fd );
  std::string partChannel( const std::string& message, int fd );
  std::string changeModes( const std::string& message, int fd );
  std::string kickoutUser( const std::string& message, int fd );
  std::string changeTopic( const std::string& message, int fd );
  std::string inviteUser( const std::string& message, int fd );
  std::string directMsg( const std::string& message, int fd );
  */

 public:
  static bool _stopServer;

  Server( char const *port, char const *password ) throw( std::exception );
  ~Server();
  Server( Server const &src );
  void serve( void ) throw( std::exception );
  void listeningLoop( void );
  std::string getPasswd() const;
  int getListeningSocket() const;

  class IncorrectPortException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "incorrect port number. Please enter a port number within acceptable range (1025 to 65535)";
    }
  };

  class IncorrectPasswordException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "incorrect server password";
    }
  };

  class BindFailException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to bind";
    }
  };

  class AddrInfoFailException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to get address info";
    }
  };
};

void  sigchld_handler( int s );

#endif
