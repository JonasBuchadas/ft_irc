#include "Connector.hpp"
#include "Server.hpp"

Connector::Connector(Server &server) : _server(server), _authenticator()
{
  _pfds.clear();
}

Connector::~Connector()
{
  clearUsers();
}

Connector::Connector( Connector const &src ) : _server(src._server), _authenticator() {
  *this = src;
}

Connector &Connector::operator=( Connector const &src ) {
  if ( this == &src )
    return ( *this );
  _pfds = src._pfds;
  return ( *this );
}

void Connector::initListener()
{
  addToPfds( _server.getListeningSocket() );
  std::cout << "server: waiting for connections..." << std::endl;
}

void Connector::monitorChanges( int stopServer )
{
  int                     newFd;
  struct sockaddr_storage remoteaddr;
  socklen_t               addrlen;
  int                     nbytes = 0;
  char                    buf[514];

  int pollCount = poll( &_pfds[0], _pfds.size(), -1 );
  if ( pollCount == -1 || stopServer )
    return ;
  for ( int i = 0; i < (int)_pfds.size(); i++ ) {
    if ( _pfds[i].revents & POLL_IN ) {
      if ( _pfds[i].fd == _server.getListeningSocket() ) {
        addrlen = sizeof( remoteaddr );
        newFd   = accept( _server.getListeningSocket(), (struct sockaddr *)&remoteaddr, &addrlen );
        if ( newFd == -1 )
          perror( "accept" );
        else
          addToPfds( newFd );
      } else {
        int senderFD = _pfds[i].fd;
        nbytes       = recv( senderFD, buf, 512, 0 );
        buf[nbytes] = '\0';
        if ( nbytes <= 0 ) {
          if ( nbytes == 0 ) {
            std::cout << "connection closed from " << senderFD << std::endl;
          } else {
            perror( "recv" );
          }
          close( senderFD );
          i -= delFromPfds( senderFD );
        } else {
          Messenger msg( _server.getListeningSocket() );
          if (nbytes >= 512)
          {
            while (recv( senderFD, buf, 512, MSG_DONTWAIT) > 0);
            msg.tooLargeAMsg( senderFD );
          }
          else
            msg.getValidMsg( _authenticator, _pfds, _users, senderFD, buf );
          if (!_users[senderFD] && _authenticator.authenticateUser(_server.getPasswd(), senderFD))
          {
              _users[senderFD] = new User(_authenticator.getUser(senderFD), _authenticator.getNick(senderFD));
              msg.LoggedInUser( senderFD );
          }
        }
      }
    }
  }
}

void Connector::addToPfds( int fd ) {
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

int Connector::delFromPfds( int fd ) {
  std::vector<pollfd>::iterator it = _pfds.begin();
  while ( it != _pfds.end() ) {
    if ( it->fd == fd ) {
      if ( _users[it->fd] ) {
        std::map<int, User *>::iterator uit = _users.find( it->fd );
        delete uit->second;
        _users.erase( uit );
      }
      _authenticator.releaseUserInfo( fd );
      _pfds.erase( it );
      return ( 1 );
    }
    ++it;
  }
  return 0;
}

void Connector::clearUsers() {
  std::map<int, User *>::iterator it;
  for ( it = _users.begin(); it != _users.end(); it++ ) {
    delete it->second;
    it->second = NULL;
  }
  
  std::vector<pollfd>::iterator fit = _pfds.begin();
  for ( fit = _pfds.begin(); fit != _pfds.end(); fit++ ) {
    close(fit->fd);
  }
  _users.clear();
}

std::string Connector::getPass( int fd )
{
  return _authenticator.getPass( fd );
}

std::string Connector::getNick( int fd )
{
  return _authenticator.getNick( fd );
}

std::string Connector::getUser( int fd )
{
  return _authenticator.getUser( fd );
}

std::string Connector::executeCommand(const std::string& command, const std::string& message, int fd)
{
  return _authenticator.executeCommand(command, message, fd);
}

int Connector::authenticateUser( std::string password, int fd )
{
  return _authenticator.authenticateUser(password, fd);
}

void Connector::releaseUserInfo( int fd )
{
  _authenticator.releaseUserInfo( fd );
}

