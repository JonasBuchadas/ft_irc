#pragma once
#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <iostream>

class Connection {
  int                _port;
  int                _socketFd;
  struct sockaddr_in _server_addr;

  Connection();
  Connection &operator=( Connection const &src );

 public:
  Connection( int port );
  ~Connection();
  Connection( Connection const &src );

  void socketBind( void ) throw( std::exception );

  class SocketFailCreationException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to create socket";
    }
  };

  class SocketFailBindException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to bind socket";
    }
  };
};

#endif
