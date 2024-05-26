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

std::vector<ParsedMsg> Parser::parseMsg( std::string msg ) {
  size_t                 start   = 0;
  std::string            message = msg;
  std::string            word;
  std::vector<ParsedMsg> msgs;

  if ( !msg.empty() && msg.find_first_of( "\n\r", start ) != std::string::npos )
    message = msg.substr( start, msg.find_first_of( "\n\r", start ) );
  while ( !message.empty() ) {
    std::stringstream ss( message );
    ss >> word;
    ParsedMsg result   = ParsedMsg();
    result.commandName = word;
    result.args        = message.substr( word.length() );
    msgs.push_back( result );
    start = msg.find_first_of( "\n\r\0", start );
    while ( start < msg.size() && ( msg[start] == '\n' || msg[start] == '\r' ) )
      start++;
    if ( start < msg.size() && msg.find_first_of( "\n\r", start ) != std::string::npos )
      message = msg.substr( start, msg.find_first_of( "\n\r", start ) - start );
    else
      break;
  }
  return msgs;
}
