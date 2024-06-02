#pragma once
#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class Channel {
 private:
  std::vector<int> _users;
  std::vector<int> _operators;

  bool         _inviteOnly;
  bool         _topicProtected;
  std::string  _topic;
  std::string  _name;
  std::string  _password;
  unsigned int _maxUsers;

 public:
  Channel(std::string name);
  ~Channel();
  Channel( Channel const &src );
  Channel &operator=( Channel const &src );

  std::vector<int> getAllUsers();
  std::vector<int> getAllOperators();
  bool             isUser( int user );
  bool             isOperator( int user );
  bool             isInviteOnly( void );
  bool             isTopicProtected( void );
  std::string      getTopic( void );
  std::string      getName( void );
  std::string      getPassword( void );
  unsigned int     getMaxUsers( void );
  void             removeUser( int _userFD );
  void             removeOperator( int _userFD );

  void addUser( int user );
  void removeUser( int user );
  void addOperator( int user );  // it will be more like void addOperator( User *user );
  void removeOperator( int user );

  void setInviteOnly( bool inviteOnly );
  void setTopicProtected( bool topicProtected );
  void setTopic( std::string topic );
  void setPassword( std::string password );
  void setMaxUsers( unsigned int maxUsers );
};

#endif
