#include "Server.hpp"

Server::Server() {}

Server::~Server() {
  free( _pfds );
}

Server::Server( Server const &src ) {
  *this = src;
}

Server &Server::operator=( Server const &src ) {
  if ( this == &src )
    return ( *this );
  _port            = src._port;
  _password        = src._password;
  _listeningSocket = src._listeningSocket;
  _server_addr     = src._server_addr;
  _pfds            = src._pfds;
  _fdCount         = src._fdCount;
  _fdSize          = src._fdSize;
  return ( *this );
}

Server::Server( char const *port, char const *password ) throw( std::exception ) {
  setPort( port );
  setPassword( password );
  setupListeningSocket();
  _fdCount = 0;
  _fdSize  = 5;
  _pfds    = (struct pollfd *)malloc( sizeof( *_pfds ) * _fdSize );
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
    perror( "listen" );
    exit( 1 );
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
  int                     nbytes;
  char                    buf[256];

  while ( 1 ) {
    int pollCount = poll( _pfds, _fdCount, -1 );

    if ( pollCount == -1 ) {
      perror( "poll" );
      exit( 1 );
    }
    for ( int i = 0; i < _fdCount; i++ ) {
      if ( _pfds[i].revents & POLL_IN ) {
        if ( _pfds[i].fd == _listeningSocket ) {
          addrlen = sizeof( remoteaddr );
          newFd   = accept( _listeningSocket, (struct sockaddr *)&remoteaddr, &addrlen );
          if ( newFd == -1 ) {
            perror( "accept" );
          } else {
            addToPfds( newFd );
            std::cout << "pollserver: new connection" << std::endl;
          }
        } else {
          int senderFD = _pfds[i].fd;
          nbytes       = recv( senderFD, buf, sizeof( buf ), 0 );
          if ( nbytes <= 0 ) {
            if ( nbytes == 0 ) {
              std::cout << "connection closed from " << senderFD;
            } else {
              perror( "recv" );
            }
            close( senderFD );
            delFromPfds( i );
          } else {
            for ( int j = 0; j < _fdCount; j++ ) {
              int destFD = _pfds[j].fd;
              if ( destFD != _listeningSocket && destFD != senderFD ) {
                if ( send( destFD, buf, nbytes, 0 ) == -1 )
                  perror( "send" );
              }
            }
          }
        }
      }
    }
  }
}

// void Server::listeningLoop( void ) {
//   while ( 1 ) {
//     sin_size = sizeof their_addr;
//     newFd    = accept( _listeningSocket, (struct sockaddr *)&their_addr, &sin_size );
//     if ( newFd == -1 ) {
//       perror( "accept" );
//       continue;
//     }
//     send( newFd, "Welcome to our IRC server. Please input username, nickname and server password.\n", 80, 0 );
//     inet_ntop( their_addr.ss_family, get_in_addr( (struct sockaddr *)&their_addr ), s, sizeof s );
//     std::cout << "server: got connection from " << s << std::endl;
//     _readFds = _master;
//     if ( select( _maxFd + 1, &_readFds, NULL, NULL, NULL ) == -1 ) {
//       perror( "select" );
//       exit( 4 );
//     }
//     std::cout << "For loop" << std::endl;
//     for ( int i = 0; i <= _maxFd; i++ ) {
//       if ( FD_ISSET( i, &_readFds ) ) {
//         if ( i == _listeningSocket ) {
//           addrlen = sizeof( remoteaddr );
//           newFd   = accept( _listeningSocket, (struct sockaddr *)&remoteaddr, &addrlen );
//           if ( newFd == -1 )
//             perror( "accept" );
//         } else {
//           FD_SET( newFd, &_master );
//           if ( newFd > _maxFd )
//             _maxFd = newFd;
//         }
//       } else {
//         nbytes = recv( i, buf, sizeof( buf ), 0 );
//         if ( nbytes <= 0 ) {
//           if ( nbytes == 0 )
//             std::cout << "selectserver: socket " << i << " hung up" << std::endl;
//           if ( nbytes < 0 )
//             perror( "recv" );
//           close( i );
//           FD_CLR( i, &_master );
//         } else {
//           std::cout << "message from user: " << buf << std::endl;
//           for ( int j = 0; j < _maxFd; j++ ) {
//             if ( FD_ISSET( j, &_master ) ) {
//               if ( j != _listeningSocket && j != i ) {
//                 if ( send( j, buf, nbytes, 0 ) == -1 )
//                   perror( "send" );
//               }
//             }
//           }
//         }
//       }
//     }
//     // sin_size = sizeof their_addr;
//     // newFd    = accept( _listeningSocket, (struct sockaddr *)&their_addr, &sin_size );
//     // if ( newFd == -1 ) {
//     //   perror( "accept" );
//     //   continue;
//     // }
//     // send( newFd, "Welcome to our IRC server. Please input username, nickname and server password.\n", 80, 0 );
//     // inet_ntop( their_addr.ss_family, get_in_addr( (struct sockaddr *)&their_addr ), s, sizeof s );
//     // std::cout << "server: got connection from " << s << std::endl;
//   }
// }

// Add a new file descriptor to the iset
void Server::addToPfds( int newfd ) {
  // If we don't have room, add more space in the pfds array
  if ( _fdCount == _fdSize ) {
    _fdSize *= 2;  // Double it
    _pfds = (struct pollfd *)realloc( _pfds, sizeof( *_pfds ) * _fdSize );
  }
  _pfds[_fdCount].fd     = newfd;
  _pfds[_fdCount].events = POLLIN;  // Check ready-to-read
  _fdCount++;
}

void Server::delFromPfds( int i ) {
  // Copy the one from the end over this one
  _pfds[i] = _pfds[_fdCount - 1];
  _fdCount--;
}

void *get_in_addr( struct sockaddr *sa ) {
  if ( sa->sa_family == AF_INET ) {
    return &( ( (struct sockaddr_in *)sa )->sin_addr );
  }
  return &( ( (struct sockaddr_in6 *)sa )->sin6_addr );
}

void sigchld_handler( int s ) {
  (void)s;
  int saved_errno = errno;
  while ( waitpid( -1, NULL, WNOHANG ) > 0 )
    ;
  errno = saved_errno;
}
