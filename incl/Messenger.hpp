#pragma once
#ifndef __MESSENGER_HPP__
#define __MESSENGER_HPP__

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

#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "Authenticator.hpp"
#include "CommandFactory.hpp"

class Messenger {
 private:
  std::vector<int> _recipients;
  std::string      _response;
  int              _listeningSocket;

  void respond();

 public:
  Messenger();
  Messenger( int listeningSocket );
  ~Messenger();
  Messenger( Messenger const &src );
  Messenger &operator=( Messenger const &src );

  void respond( PreparedResponse pr ) throw( std::exception );

  class BadRespondException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "Bad response.";
    }
  };
};

#endif
