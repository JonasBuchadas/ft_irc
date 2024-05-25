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

  /*
  _command["JOIN"] =  &Server::joinChannel;
  _command["PART"] =  &Server::partChannel;
  _command["MODE"] =  &Server::changeModes;
  _command["KICK"] =  &Server::kickoutUser;
  _command["TOPIC"] = &Server::changeTopic;
  _command["INVITE"] = &Server::inviteUser;
  _command["PRIVMSG"] = &Server::directMsg;
  */

 public:
  Messenger();
  Messenger( int listeningSocket );
  ~Messenger();
  Messenger( Messenger const &src );
  Messenger &operator=( Messenger const &src );

  void getValidMsg( Authenticator *auth, int fd, std::string msg );
  void LoggedInUser( int senderFD );

  class BadRespondException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "Bad response.";
    }
  };
};

#endif
