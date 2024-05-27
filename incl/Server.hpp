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
#include <sstream>
#include <vector>

#include "ACommand.hpp"
#include "Authenticator.hpp"
#include "Messenger.hpp"
#include "Parser.hpp"
#include "User.hpp"

class User;
class Authenticator;

#define BACKLOG 10

class Server {
 private:
  const char         *_port;
  std::string         _password;
  int                 _listeningSocket;
  int                 _fdSize;
  std::vector<pollfd> _pfds;

  Parser         _parser;
  Authenticator *_authenticator;
  CommandFactory _commandFactory;
  Messenger      _messenger;

  void addToPfds( int fd );
  int  delFromPfds( int fd );
  void clearUsers();

  Server();
  Server &operator=( Server const &src );

  void        setPort( const char *port ) throw( std::exception );
  void        setPassword( char const *password ) throw( std::exception );
  void        setupListeningSocket( void ) throw( std::exception );
  bool        isServerConnection( int i );
  bool        isServerReceivingMessage( int i );
  void        acceptConnection( void ) throw( std::exception );
  std::string receiveMessage( int i, int senderFD ) throw( std::exception );

 public:
  static bool _stopServer;

  Server( char const *port, char const *password ) throw( std::exception );
  ~Server();
  Server( Server const &src );
  void serve( void ) throw( std::exception );
  void listeningLoop( void );
  int  getListeningSocket() const;

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

  class ListenFailException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to listen on socket";
    }
  };

  class SocketSetupException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to setup socket";
    }
  };

  class NewConnectionException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to accept new connection";
    }
  };

  class RecvFailException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to receive message";
    }
  };
};

void sigchld_handler( int s );

#endif
