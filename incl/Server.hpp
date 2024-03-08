#pragma once
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <iostream>

#include "Connection.hpp"

class Server {
 private:
  int         _port;
  std::string _password;

  Server();
  Server &operator=( Server const &src );

  void setPort( const char *port ) throw( std::exception );
  void setPassword( char const *password ) throw( std::exception );

 public:
  Server( char const *port, char const *password ) throw( std::exception );
  ~Server();
  Server( Server const &src );
  void serve( void ) throw( std::exception );

  class IncorrectPortException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "incorrect port number";
    }
  };

  class IncorrectPasswordException : public std::exception {
   public:
    virtual const char *what() const throw() {
      return "incorrect server password";
    }
  };
};

#endif
