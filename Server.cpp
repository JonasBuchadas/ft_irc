#include "Server.hpp"

Server::Server() {}

Server::~Server() {}

Server::Server( Server const &src ) {
  *this = src;
}

Server &Server::operator=( Server const &src ) {
  if ( this == &src )
    return ( *this );
  // TODO Assign Server Atributes
  return ( *this );
}
