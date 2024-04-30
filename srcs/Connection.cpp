#include "Connection.hpp"

Connection::Connection() {}

Connection::~Connection() {}

Connection::Connection( Connection const &src ) {
  *this = src;
}

Connection &Connection::operator=( Connection const &src ) {
  if ( this == &src )
    return ( *this );
  _port        = src._port;
  _socketFd    = src._socketFd;
  _server_addr = src._server_addr;
  return ( *this );
}

Connection::Connection( int port ) : _port( port ) {}

void Connection::socketBind() throw( std::exception ) {
  if ( ( _socketFd = socket( AF_INET6, SOCK_STREAM, 0 ) ) == -1 ) {
    throw Connection::SocketFailCreationException();
  }

  memset( &_server_addr, 0, sizeof( _server_addr ) );
  _server_addr.sin_family      = AF_INET6;
  _server_addr.sin_port        = htons( _port );
  _server_addr.sin_addr.s_addr = INADDR_ANY;

  if ( bind( _socketFd, (struct sockaddr *)&_server_addr, sizeof( _server_addr ) ) == -1 ) {
    throw Connection::SocketFailBindException();
  }
}
