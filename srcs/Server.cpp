#include "Server.hpp"

Server::Server() {}

Server::~Server() {
  
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
  _fdSize          = src._fdSize;
  return ( *this );
}

Server::Server( char const *port, char const *password ) throw( std::exception ) {
  setPort( port );
  setPassword( password );
  setupListeningSocket();
  _fdSize = 5;
  _users.clear();
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

void Server::handleClient( int fd )
{
  char buffer[1024];
  int valread;
  static std::string pass, nick, name;

  while ((valread = read(fd, buffer, sizeof( buffer ))) > 0) {
      buffer[valread] = '\0';
      std::string msg(buffer);
      std::string message = msg.substr(0, msg.length() - 1);
      if (message.length() > 4 && message.compare(0, 4, "PASS") == 0)
        pass = message.substr(5);
      else if (message.length() > 4 && message.compare(0, 4, "NICK") == 0)
      {
        for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
        {
          if (it->second && it->second->_nickName == message.substr(5) && it->first != fd)
          {
            std::cout << "Nick already taken" << std::endl;
            return ;
          }
        }
        nick = message.substr(5);
      }
      else if (message.length() > 4 && message.compare(0, 4, "USER") == 0)
      {
        for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); it++)
        {
          if (it->second && it->second->_serverName == message.substr(5) && it->first != fd)
          {
            std::cout << "Name already taken" << std::endl;
            return ;
          }
        }
        name = message.substr(5);
      }
      else if (_users[fd])
        std::cout << message << std::endl;
      if (!_users[fd] && pass == _password && !nick.empty() && !name.empty())
      {
        _users[fd] = new User(name, nick);
        pass.clear();
        nick.clear();
        name.clear();
      }
  }
  // close(fd);
}

void Server::listeningLoop( void ) {
  int                     newFd;
  struct sockaddr_storage remoteaddr;
  socklen_t               addrlen;
  int                     nbytes = 0;
  char                    buf[256];

  while ( 1 ) {
    int pollCount = poll(&_pfds[0], _pfds.size(), -1 );
    if ( pollCount == -1 ) {
      perror( "poll" );
      exit( 1 );
    }
    for ( int i = 0; i < (int)_pfds.size(); i++ ) {
      if ( _pfds[i].revents & POLL_IN ) {
        if ( _pfds[i].fd == _listeningSocket ) {
          addrlen = sizeof( remoteaddr );
          newFd   = accept( _listeningSocket, (struct sockaddr *)&remoteaddr, &addrlen );
          if ( newFd == -1 )
            perror( "accept" );
          else
          {
            addToPfds( newFd );
            handleClient( newFd );
          }
        } else {
          int senderFD = _pfds[i].fd;
          nbytes       = recv( senderFD, buf, sizeof( buf ), 0 );
          if ( nbytes <= 0 ) {
            if ( nbytes == 0 ) {
              std::cout << "connection closed from " << senderFD << std::endl;
            } else {
              perror( "recv" );
            }
            close( senderFD );
            i -= delFromPfds( senderFD );
          } else {
            for ( int j = 0; j < (int)_pfds.size(); j++ ) {
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
  pollfd server_fd;
  server_fd.fd = newfd;
  server_fd.events = POLLIN;  // Check ready-to-read
  server_fd.revents = 0;
  std::vector<pollfd>::iterator it = _pfds.begin();
  while (it != _pfds.end()) {
      if (it->fd == newfd)
          return ;
      ++it;
  }
  _pfds.push_back(server_fd);
  std::cout << "pollserver: new connection" << std::endl;
}

int Server::delFromPfds( int i ) {
  // Copy the one from the end over this one
  std::vector<pollfd>::iterator it = _pfds.begin();
  while (it != _pfds.end())
  {
      if (it->fd == i)
      {
        if (_users[it->fd])
        {
          std::map<int,User *>::iterator uit = _users.find(it->fd);
          delete uit->second;
          _users.erase(uit);
        }
        _pfds.erase(it);
        return (1);
      }
      ++it;
  }
  return 0;
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
