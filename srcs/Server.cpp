#include "Server.hpp"

Server::Server() {}

Server::~Server() {}

Server::Server( Server const &src ) {
  *this = src;
}

Server &Server::operator=( Server const &src ) {
  if ( this == &src )
    return ( *this );
  _port     = src._port;
  _password = src._password;
  return ( *this );
}

Server::Server( char const *port, char const *password ) throw( std::exception ) {
  setPort( port );
  setPassword( password );
}

void Server::setPassword( char const *password ) throw( std::exception ) {
  if ( !password )
    throw Server::IncorrectPasswordException();
  _password = password;
}

void Server::setPort( char const *port ) throw( std::exception ) {
  if ( !port )
    throw Server::IncorrectPortException();
  for ( int i = -1; port[i]; ++i ) {
    if ( !std::isdigit( port[i] ) ) {
      throw Server::IncorrectPortException();
    }
  }
  _port = atoi( port );
}

void Server::serve( void ) throw( std::exception ) {
  Connection c = Connection( _port );
  c.socketBind();
}
