#include "Server.hpp"

#include "GenResponse.hpp"

bool Server::_stopServer = false;

Server::Server() : _authenticator("invalid") {}

Server::~Server() {
  clearUsers();
}

Server::Server( Server const &src ) : _authenticator(src._authenticator) {
  *this = src;
}

Server &Server::operator=( Server const &src ) {
  if ( this == &src )
    return ( *this );
  _port            = src._port;
  _password        = src._password;
  _listeningSocket = src._listeningSocket;
  _fdSize          = src._fdSize;
  _pfds            = src._pfds;
  return ( *this );
}

Server::Server( char const *port, char const *password ) throw( std::exception ) : _authenticator( _password.c_str() ) {
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
  addToPfds( _listeningSocket );
  std::cout << "server: waiting for connections..." << std::endl;
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
  int                     newFd;
  struct sockaddr_storage remoteaddr;
  socklen_t               addrlen;
  int                     nbytes = 0;
  char                    buf[514];

  signal( SIGINT, sigchld_handler );
  signal( SIGQUIT, sigchld_handler );
  while ( 1 ) {
    int pollCount = poll( &_pfds[0], _pfds.size(), -1 );
    if ( pollCount == -1 || _stopServer )
      return;
    for ( int i = 0; i < (int)_pfds.size(); i++ ) {
      if ( _pfds[i].revents & POLL_IN ) {
        if ( _pfds[i].fd == _listeningSocket ) {
          addrlen = sizeof( remoteaddr );
          newFd   = accept( _listeningSocket, (struct sockaddr *)&remoteaddr, &addrlen );
          if ( newFd == -1 )
            perror( "accept" );
          else
            addToPfds( newFd );
        } else {
          int senderFD = _pfds[i].fd;
          nbytes       = recv( senderFD, buf, 512, 0 );
          buf[nbytes]  = '\0';
          if ( nbytes <= 0 ) {
            if ( nbytes == 0 ) {
              std::cout << "connection closed from " << senderFD << std::endl;
            } else {
              perror( "recv" );
            }
            close( senderFD );
            i -= delFromPfds( senderFD );
          } else {
            Messenger msg( _listeningSocket );
            if ( nbytes >= 512 ) {
              while ( recv( senderFD, buf, 512, MSG_DONTWAIT ) > 0 )
                ;
              msg.tooLargeAMsg( senderFD );
            } else
              msg.getValidMsg( _authenticator, senderFD, buf );
            if ( _authenticator.authenticateUser( senderFD ) ) {
                msg.LoggedInUser( senderFD );
            }
          }
        }
      }
    }
  }
}

void Server::addToPfds( int fd ) {
  pollfd server_fd;
  server_fd.fd                     = fd;
  server_fd.events                 = POLLIN;
  server_fd.revents                = 0;
  std::vector<pollfd>::iterator it = _pfds.begin();
  while ( it != _pfds.end() ) {
    if ( it->fd == fd )
      return;
    ++it;
  }
  _pfds.push_back( server_fd );
  std::cout << "pollserver: new connection" << std::endl;
}

int Server::delFromPfds( int fd ) {
  std::vector<pollfd>::iterator it = _pfds.begin();
  while ( it != _pfds.end() ) {
    if ( it->fd == fd ) {
      _authenticator.releaseUserInfo( fd );
      _pfds.erase( it );
      return ( 1 );
    }
    ++it;
  }
  return 0;
}

void Server::clearUsers() {
  std::vector<pollfd>::iterator fit = _pfds.begin();
  for ( fit = _pfds.begin(); fit != _pfds.end(); fit++ ) {
    close( fit->fd );
  }
  _pfds.clear();
}

std::string Server::executeCommand( const std::string &command, const std::string &message, int fd ) {
  return _authenticator.executeCommand( command, message, fd );
}

void sigchld_handler( int s ) {
  (void)s;
  Server::_stopServer = true;
  close( 3 );
}
