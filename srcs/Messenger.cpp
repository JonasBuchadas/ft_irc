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
  std::map<std::string, std::vector<int> >::iterator resps = pr.allresponses.begin();
  for ( ; resps != pr.allresponses.end(); resps++ )
  {
    for ( int j = 0; j < (int)resps->second.size(); j++ ) {
      int destFD = resps->second[j];
      if ( send( destFD, resps->first.c_str(), resps->first.size(), 0 ) == -1 )
        throw BadRespondException();
    }
  }
}
