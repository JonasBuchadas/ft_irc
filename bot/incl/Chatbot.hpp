#pragma once
#ifndef __CHATBOT_HPP__
#define __CHATBOT_HPP__

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <csignal>
#include <cstring>
#include <exception>
#include <iostream>
#include <map>

#include "CommandFactory.hpp"

class Chatbot {
 private:
  Chatbot( Chatbot const &src );
  Chatbot &operator=( Chatbot const &src );

 public:
  Chatbot();
  ~Chatbot();

  std::string awaitInput( int sockfd );
  void        loginBossBot( int sockfd, char **av );
  int         connectToServer( char *port );
  void        listeningLoop( char **av );

  class CouldntConnecttoServer : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to connect";
    }
  };

  class CouldntLoginBot : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to login";
    }
  };

  class RecvFailException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to receive message";
    }
  };

  class SendFailException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "failed to send message";
    }
  };
};

#endif
