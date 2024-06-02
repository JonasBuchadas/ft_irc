#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {
}

Parser::Parser( Parser const &src ) {
  *this = src;
}

Parser &Parser::operator=( Parser const &src ) {
  if ( this == &src )
    return ( *this );
  return ( *this );
}

std::vector<ParsedMsg> Parser::parseMsg( UnparsedMsg m ) {
  size_t                 start   = 0;
  std::string            message = m.message;
  std::string            word;
  std::vector<ParsedMsg> msgs;

  if ( !m.message.empty() && m.message.find_first_of( "\n\r", start ) != std::string::npos )
    message = m.message.substr( start, m.message.find_first_of( "\n\r", start ) );
  while ( !message.empty() ) {
    std::stringstream ss( message );
    ss >> word;
    ParsedMsg result   = ParsedMsg();
    result.commandName = word;
    result.args        = message.substr( word.length() );
    result.internal    = m.internal;
    msgs.push_back( result );
    start = m.message.find_first_of( "\n\r\0", start );
    while ( start < m.message.size() && ( m.message[start] == '\n' || m.message[start] == '\r' ) )
      start++;
    if ( start < m.message.size() && m.message.find_first_of( "\n\r", start ) != std::string::npos )
      message = m.message.substr( start, m.message.find_first_of( "\n\r", start ) - start );
    else
      break;
  }
  return msgs;
}
