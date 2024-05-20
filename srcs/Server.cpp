#include "Server.hpp"

#include "GenResponse.hpp"

bool Server::_stopServer = false;

Server::Server() : _connector( *this ) {}

Server::~Server() {}

Server::Server( Server const &src ) : _connector( *this ) {
  *this = src;
}

Server &Server::operator=( Server const &src ) {
  if ( this == &src )
    return ( *this );
  _port            = src._port;
  _password        = src._password;
  _listeningSocket = src._listeningSocket;
  _fdSize          = src._fdSize;
  return ( *this );
}

Server::Server( char const *port, char const *password ) throw( std::exception ) : _connector( *this ) {
  setPort( port );
  setPassword( password );
  setupListeningSocket();
  _fdSize = 5;
}

void Server::setPassword( char const *password ) throw( std::exception ) {
  if ( !password[0] )
    throw Server::IncorrectPasswordException();
  _password = password;
}

void Server::setPort( char const *port ) throw( std::exception ) {
  if ( !port[0] )
    throw Server::IncorrectPortException();
  for ( int i = 0; port[i]; i++ ) {
    if ( !std::isdigit( port[i] ) )
      throw Server::IncorrectPortException();
  }
  int portInt = atoi( port );
  if ( portInt <= 1024 || portInt >= 65535 )
    throw Server::IncorrectPortException();
  _port = port;
}

void Server::serve( void ) throw( std::exception ) {
  if ( listen( _listeningSocket, BACKLOG ) == -1 ) {
    perror( "listen" );  // Single throw plz!
    exit( 1 );           // Single throw plz!
  }
  _connector.initListener();
  listeningLoop();
}

void Server::setupListeningSocket( void ) throw( std::exception ) {
  int             yes = 1;
  struct addrinfo hints, *res, *p;
  memset( &hints, 0, sizeof( hints ) );
  hints.ai_family   = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags    = AI_PASSIVE;
  if ( getaddrinfo( NULL, _port, &hints, &res ) != 0 )
    throw Server::AddrInfoFailException();
  for ( p = res; p != NULL; p = p->ai_next ) {
    if ( ( _listeningSocket = socket( p->ai_family, p->ai_socktype, p->ai_protocol ) ) == -1 ) {
      perror( "server: socket" );
      continue;
    }
    if ( setsockopt( _listeningSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == -1 ) {
      perror( "setsockopt" );
      return;
    }
    if ( bind( _listeningSocket, p->ai_addr, p->ai_addrlen ) == -1 ) {
      close( _listeningSocket );
      perror( "server: bind" );
      continue;
    }
    break;
  }
  freeaddrinfo( res );
  if ( p == NULL )
    throw Server::BindFailException();
}

void Server::listeningLoop( void ) {
  signal( SIGINT, sigchld_handler );
  signal( SIGQUIT, sigchld_handler );
  while ( !_stopServer ) {
    _connector.monitorChanges( _stopServer );
  }
}

void sigchld_handler( int s ) {
  (void)s;
  Server::_stopServer = true;
  close( 3 );
}

std::string Server::getPasswd() const {
  return _password;
}

int Server::getListeningSocket() const {
  return _listeningSocket;
}
