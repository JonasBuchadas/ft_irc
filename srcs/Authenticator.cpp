#include "Authenticator.hpp"

Authenticator::Authenticator() {
  _users.clear();
  _passlist.clear();
  _nicklist.clear();
  _namelist.clear();
  _command.clear();
  _command["PASS"] = &Authenticator::checkPasswd;
  _command["NICK"] = &Authenticator::setNickname;
  _command["USER"] = &Authenticator::setUsername;
}

Authenticator::~Authenticator() {}

Authenticator::Authenticator( Authenticator const& src ) {
  *this = src;
}

Authenticator& Authenticator::operator=( Authenticator const& src ) {
  if ( this == &src )
    return ( *this );
  _users    = src._users;
  _passlist = src._passlist;
  _nicklist = src._nicklist;
  _namelist = src._namelist;
  return ( *this );
}

bool Authenticator::isValidArg( std::string str ) {
  for ( size_t i = 0; i < str.length(); i++ )
    if ( !isdigit( str[i] ) && !isalpha( str[i] ) )
      return 0;
  return 1;
}

std::string Authenticator::checkPasswd( const std::string& message, int fd ) {
  if ( message.length() <= 1 )
    return "Invalid string\n\0";
  std::string str = message.substr( 1, message.find_first_of( "\n\r\0", 1 ) - 1 );
  if ( !_passlist[fd].empty() && isValidArg( str ) ) {
    _passlist[fd] = str;
    return "Password successfully updated\n\0";
  }
  if ( isValidArg( str ) ) {
    _passlist[fd] = str;
    return "Registered password\n\0";
  } else
    return "Password contains invalid characters\n\0";
}

std::string Authenticator::setNickname( const std::string& message, int fd ) {
  if ( message.length() <= 1 )
    return "Invalid string\n\0";
  std::string str = message.substr( 1, message.find_first_of( "\n\r\0", 1 ) - 1 );
  for ( std::map<int, std::string>::iterator it = _nicklist.begin(); it != _nicklist.end(); it++ ) {
    if ( it->first != fd && it->second == str )
      return "Nickname already taken. Nickname not updated\n\0";
  }
  if ( !_nicklist[fd].empty() && isValidArg( str ) ) {
    _nicklist[fd] = str;
    return "Nickname successfully updated\n\0";
  }
  if ( isValidArg( str ) ) {
    _nicklist[fd] = str;
    return "Registered your nickname \n\0";
  } else
    return "Nickname contains invalid characters\n\0";
}

bool Authenticator::userNameExists( int fd, std::string userName ) {
  for ( std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++ ) {
    if ( it->first != fd && it->second->getName() == userName )
      return true;
  }
  return false;
}

bool Authenticator::nickNameExists( int fd, std::string nickName ) {
  for ( std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++ ) {
    if ( it->first != fd && it->second->getNick() == nickName )
      return true;
  }
  return false;
}

std::string Authenticator::setUsername( const std::string& message, int fd ) {
  if ( message.length() <= 1 )
    return "Invalid string\n\0";
  std::string str = message.substr( 1, message.find_first_of( " \n\r\0", 1 ) - 1 );
  for ( std::map<int, std::string>::iterator it = _namelist.begin(); it != _namelist.end(); it++ ) {
    if ( it->first != fd && it->second == str )
      return "Username already taken. Username not updated\n\0";
  }
  if ( !_namelist[fd].empty() && isValidArg( str ) ) {
    _namelist[fd] = str;
    return "Username successfully updated\n\0";
  }
  if ( isValidArg( str ) ) {
    _namelist[fd] = str;
    return "Registered your username\n\0";
  } else
    return "Username contains invalid characters\n\0";
}

std::string Authenticator::getPass( int fd ) {
  return _passlist[fd];
}

std::string Authenticator::getNick( int fd ) {
  return _nicklist[fd];
}

User* Authenticator::getUser( int fd ) {
  std::map<int, User*>::iterator it = _users.find( fd );
  if ( it == _users.end() )
    return NULL;
  return it->second;
}

void Authenticator::addUser( int fd, User* user ) {
  _users[fd] = user;
}

bool Authenticator::authenticateUser( std::string password, int fd ) {
  int pass = false, nick = false, user = false;

  if ( !_passlist[fd].empty() && _passlist[fd] == password )
    pass = true;
  if ( !_nicklist[fd].empty() )
    nick = true;
  if ( !_namelist[fd].empty() )
    user = true;

  if ( pass && nick && user )
    return true;
  return false;
}

void Authenticator::releaseUserInfo( int fd ) {
  // _users.erase( fd );
  if ( !_passlist[fd].empty() )
    _passlist.erase( fd );
  if ( !_nicklist[fd].empty() )
    _nicklist.erase( fd );
  if ( !_namelist[fd].empty() )
    _namelist.erase( fd );
}

std::string Authenticator::executeCommand( const std::string& command, const std::string& message, int fd ) {
  std::map<std::string, CommandFunction>::iterator it = _command.find( command );
  if ( it != _command.end() ) {
    return ( this->*( it->second ) )( message, fd );
  } else {
    return "";
  }
}

void Authenticator::clearUsers() {
  std::map<int, User*>::iterator it;
  for ( it = _users.begin(); it != _users.end(); it++ ) {
    delete it->second;
    it->second = NULL;
  }
  _users.clear();
}
