#include "Message.hpp"

Message::Message() {}

Message::~Message() {
  delete _timestamp;
}

Message::Message( Message const &src ) {
  *this = src;
}

Message &Message::operator=( Message const &src ) {
  if ( this == &src )
    return ( *this );
  _author    = src._author;
  _channel   = src._channel;
  _timestamp = src._timestamp;
  _msg       = src._msg;
  return ( *this );
}
