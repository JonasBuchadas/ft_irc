#include "Authenticator.hpp"

Authenticator::Authenticator( const char* password ) : _password( password ) {
  _users.clear();
  _command.clear();
  // _command["PASS"] = &Authenticator::checkPasswd;
  // _command["NICK"] = &Authenticator::setNickname;
  // _command["USER"] = &Authenticator::setUsername;
}

Authenticator::~Authenticator() {
  // for ( std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++ ) {
  //   delete it->second;
  //   it->second = NULL;
  // }
}

Authenticator::Authenticator( Authenticator const& src ) {
  *this = src;
}

Authenticator& Authenticator::operator=( Authenticator const& src ) {
  if ( this == &src )
    return ( *this );
  _users = src._users;
  return ( *this );
}

bool Authenticator::isValidArg( std::string str ) {
  for ( size_t i = 0; i < str.length(); i++ )
    if ( !isdigit( str[i] ) && !isalpha( str[i] ) )
      return 0;
  return 1;
}

// std::string Authenticator::checkPasswd( const std::string& message, int fd ) {
//   if ( message.length() <= 1 )
//     return "Invalid string\n\0";
//   std::string str = message.substr( 1, message.find_first_of( "\n\r\0", 1 ) - 1 );
//   if ( isValidArg( str ) ) {
//     if ( _users.find( fd ) == _users.end() )
//       _users[fd] = new User;
//     if ( str == _password )
//       _users[fd]->setPassword( true );
//     else
//       _users[fd]->setPassword( false );
//     return "Password was registered\n\0";
//   } else
//     return "Password contains invalid characters\n\0";
// }

// std::string Authenticator::setNickname( const std::string& message, int fd ) {
//   if ( message.length() <= 1 )
//     return "Invalid string\n\0";
//   std::string str = message.substr( 1, message.find_first_of( "\n\r\0", 1 ) - 1 );
//   for ( std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++ ) {
//     if ( it->first != fd && it->second->getNick() == str )
//       return "Nickname already taken. Nickname not updated\n\0";
//   }
//   if ( _users[fd] && isValidArg( str ) ) {
//     _users[fd]->setNick( str );
//     return "Nickname successfully updated\n\0";
//   } else if ( isValidArg( str ) ) {
//     _users[fd] = new User;
//     _users[fd]->setNick( str );
//     return "Registered your nickname \n\0";
//   } else
//     return "Nickname contains invalid characters\n\0";
// }

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

// std::string Authenticator::setUsername( const std::string& message, int fd ) {
//   if ( message.length() <= 1 )
//     return "Invalid string\n\0";
//   std::string str = message.substr( 1, message.find_first_of( " \n\r\0", 1 ) - 1 );
//   for ( std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++ ) {
//     if ( it->first != fd && it->second->getName() == str )
//       return "Username already taken. Username not updated\n\0";
//   }
//   if ( _users[fd] && isValidArg( str ) ) {
//     _users[fd]->setName( str );
//     return "Username successfully updated\n\0";
//   } else if ( isValidArg( str ) ) {
//     _users[fd] = new User;
//     _users[fd]->setName( str );
//     return "Registered your username\n\0";
//   } else
//     return "Username contains invalid characters\n\0";
// }

bool Authenticator::getPass( int fd ) {
  return _users[fd]->getPassword();
}

std::string Authenticator::getNick( int fd ) {
  return _users[fd]->getNick();
}

User* Authenticator::getUser( int fd ) {
  std::map<int, User*>::iterator it = _users.find( fd );
  if ( it == _users.end() )
    return NULL;
  return it->second;
}

std::string Authenticator::getServerPass() {
  return _password;
}

std::map<int, User*> Authenticator::getAllUsers() {
  return _users;
}

void Authenticator::addUser( int fd, User* user ) {
  _users[fd] = user;
}

bool Authenticator::authenticateUser( int fd ) {
  if ( _users[fd] && !_users[fd]->getLoggedIn() && _users[fd]->getPassword() && !_users[fd]->getNick().empty() && !_users[fd]->getName().empty() ) {
    _users[fd]->setLoggedIn( true );
    return true;
  }
  return false;
}

void Authenticator::releaseUserInfo( int fd ) {
  if ( _users.find( fd ) != _users.end() ) {
    delete _users[fd];
    _users.erase( fd );
  }
}

// std::string Authenticator::executeCommand( const std::string& command, const std::string& message, int fd ) {
//   std::map<std::string, CommandFunction>::iterator it = _command.find( command );
//   if ( it != _command.end() ) {
//     return ( this->*( it->second ) )( message, fd );
//   } else {
//     return "";
//   }
// }

void Authenticator::clearUsers() {
  std::map<int, User*>::iterator it;
  for ( it = _users.begin(); it != _users.end(); it++ ) {
    delete it->second;
    it->second = NULL;
  }
  _users.clear();
}
