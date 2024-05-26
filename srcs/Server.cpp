#include "Server.hpp"

#include "Message.hpp"

bool Server::_stopServer = false;

Server::Server() {
  _authenticator = new Authenticator( "invalid" );
}

Server::~Server() {
  clearUsers();
  delete _authenticator;
}

Server::Server( Server const &src ) : _authenticator( src._authenticator ) {
  *this = src;
}

Server &Server::operator=( Server const &src ) {
  if ( this == &src )
    return ( *this );
  _port            = src._port;
  _password        = src._password;
  _listeningSocket = src._listeningSocket;
  _parser          = src._parser;
  _messenger       = src._messenger;
  _fdSize          = src._fdSize;
  _pfds            = src._pfds;
  return ( *this );
}

Server::Server( char const *port, char const *password ) throw( std::exception ) {
  setPort( port );
  setPassword( password );
  setupListeningSocket();
  _parser        = Parser();
  _authenticator = new Authenticator( _password.c_str() );
  _messenger     = Messenger( _listeningSocket );
  _fdSize        = 5;
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
  if ( listen( _listeningSocket, BACKLOG ) == -1 )
    throw ListenFailException();
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
      throw Server::SocketSetupException();
      // continue;
    }
    if ( setsockopt( _listeningSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == -1 ) {
      throw Server::SocketSetupException();
    }
    if ( bind( _listeningSocket, p->ai_addr, p->ai_addrlen ) == -1 ) {
      close( _listeningSocket );
      throw Server::BindFailException();
      // continue;
    }
    break;
  }
  freeaddrinfo( res );
  if ( p == NULL )
    throw Server::BindFailException();
}

void Server::listeningLoop( void ) {
  std::string            str;
  std::vector<ParsedMsg> parsedMsgs;
  ACommand              *command;
  std::string            response;

  signal( SIGINT, sigchld_handler );
  signal( SIGQUIT, sigchld_handler );
  while ( 1 ) {
    int pollCount = poll( &_pfds[0], _pfds.size(), -1 );
    if ( pollCount == -1 || _stopServer )
      return;
    for ( int i = 0; i < (int)_pfds.size(); i++ ) {
      try {
        if ( isServerConnection( i ) )
          acceptConnection();
        if ( isServerReceivingMessage( i ) ) {
          int senderFD = _pfds[i].fd;

          str        = receiveMessage( i, senderFD );
          parsedMsgs = _parser.parseMsg( str );
          for ( std::vector<ParsedMsg>::iterator it = parsedMsgs.begin(); it != parsedMsgs.end(); it++ ) {
            command             = _commandFactory.makeCommand( _authenticator, senderFD, it->commandName, it->args );
            PreparedResponse pr = command->execute();
            delete command;
            _messenger.respond( pr );
          }
        }
      } catch ( std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        continue;
      }
    }
  }
}

bool Server::isServerConnection( int i ) {
  return ( _pfds[i].revents & POLL_IN && _pfds[i].fd == _listeningSocket );
}

bool Server::isServerReceivingMessage( int i ) {
  return ( _pfds[i].revents & POLL_IN && _pfds[i].fd != _listeningSocket );
}

void Server::acceptConnection( void ) throw( std::exception ) {
  int                     newFd;
  struct sockaddr_storage remoteaddr;
  socklen_t               addrlen;

  addrlen = sizeof( remoteaddr );
  newFd   = accept( _listeningSocket, (struct sockaddr *)&remoteaddr, &addrlen );
  if ( newFd == -1 )
    throw Server::NewConnectionException();
  addToPfds( newFd );
}

std::string Server::receiveMessage( int i, int senderFD ) throw( std::exception ) {
  int         nbytes = 0;
  char        buf[514];
  std::string message;

  nbytes = recv( senderFD, buf, 512, 0 );
  if ( nbytes < 0 )
    throw Server::RecvFailException();
  if ( nbytes == 0 ) {
    std::cout << "connection closed from " << senderFD << std::endl;
    close( senderFD );
    i -= delFromPfds( senderFD );
  }
  buf[nbytes] = '\0';
  message     = buf;
  memset( buf, '\0', sizeof( buf ) );
  while ( nbytes >= 512 ) {
    nbytes = recv( senderFD, buf, 512, MSG_DONTWAIT );
    if ( nbytes < 0 )
      throw Server::RecvFailException();
    message += buf;
    memset( buf, '\0', sizeof( buf ) );
  }
  return message;
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
      _authenticator->releaseUserInfo( fd );
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

// std::string Server::executeCommand( const std::string &command, const std::string &message, int fd ) {
//   return _authenticator->executeCommand( command, message, fd );
// }

void sigchld_handler( int s ) {
  (void)s;
  Server::_stopServer = true;
  close( 3 );
}
