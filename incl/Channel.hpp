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
  std::vector<int> _invitees;

  bool         _inviteOnly;
  bool         _topicProtected;
  std::string  _topic;
  std::string  _name;
  std::string  _password;
  unsigned int _maxUsers;
  Channel();

 public:
  Channel( std::string name );
  ~Channel();
  Channel( Channel const &src );
  Channel &operator=( Channel const &src );

  std::vector<int> getAllMembersSansUser( int user, int target );
  std::vector<int> getAllUsers();
  std::vector<int> getAllOperators();
  bool             isUser( int user );
  bool             isOperator( int user );
  bool             isInvitee( int user );
  bool             isInviteOnly( void );
  bool             isTopicProtected( void );
  std::string      getTopic( void );
  std::string      getName( void );
  std::string      getPassword( void );
  unsigned int     getMaxUsers( void );
  std::string      getModes( void );
  void             addUser( int _userFD );
  void             addOperator( int _userFD );
  void             addInvitee( int _userFD );
  void             removeUser( int _userFD );
  void             removeOperator( int _userFD );
  void             removeInvitee( int _userFD );

  void setInviteOnly( bool inviteOnly );
  void setTopicProtected( bool topicProtected );
  void setTopic( std::string topic );
  void setPassword( std::string password );
  void setMaxUsers( unsigned int maxUsers );
};

#endif
