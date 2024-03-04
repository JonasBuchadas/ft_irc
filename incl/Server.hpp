#pragma once
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <iostream>

class Server {
 private:
 public:
  Server();
  ~Server();
  Server( Server const &src );
  Server &operator=( Server const &src );
};

#endif
