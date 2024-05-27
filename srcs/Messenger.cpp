#include "Messenger.hpp"

Messenger::Messenger() {}

Messenger::Messenger( int listeningSocket ) {
  _listeningSocket = listeningSocket;
}

Messenger::~Messenger() {}

Messenger::Messenger( Messenger const &src ) {
  *this       = src;
  _recipients = src._recipients;
}

Messenger &Messenger::operator=( Messenger const &src ) {
  if ( this == &src )
    return ( *this );
  return ( *this );
}

void Messenger::respond( PreparedResponse pr ) throw( std::exception ) {
  for ( int j = 0; j < (int)pr.recipients.size(); j++ ) {
    int destFD = pr.recipients[j];
    if ( send( destFD, pr.response.c_str(), pr.response.size(), 0 ) == -1 )
      throw BadRespondException();
  }
}
