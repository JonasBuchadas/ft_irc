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
#include <vector>
#include <iostream>

#define BACKLOG 10

class Server {
 private:
  const char        *_port;
  std::string        _password;
  int                _listeningSocket;
  int                _fdSize;
  std::vector<pollfd> _pfds;
  struct sockaddr_in _server_addr;

  Server();
  Server &operator=( Server const &src );

  void setPort( const char *port ) throw( std::exception );
  void setPassword( char const *password ) throw( std::exception );
  void setupListeningSocket( void ) throw( std::exception );
  void addToPfds( int newfd );
  void delFromPfds( int i );

 public:
  Server( char const *port, char const *password ) throw( std::exception );
  ~Server();
  Server( Server const &src );
  void serve( void ) throw( std::exception );
  void listeningLoop( void );

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
void *get_in_addr( struct sockaddr *sa );

#endif
