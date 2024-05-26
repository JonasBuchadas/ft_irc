#pragma once
#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <iostream>
#include <map>

#include "User.hpp"

class Channel {
 private:
  std::map<std::string, User> _users;
  User                       *_operators; // Should be a vector or list

  bool                        _inviteOnly;
  bool                        _topicProtected;
  std::string                 _topic;
  std::string                 _name;
  std::string                 _password;
  unsigned int                _maxUsers;

 public:
  Channel();
  ~Channel();
  Channel( Channel const &src );
  Channel &operator=( Channel const &src );

  User *getUser( std::string user );
  User *getOperator( void );
  bool  isInviteOnly( void );
  bool  isTopicProtected( void );
  std::string getTopic( void );
  std::string getName( void );
  std::string getPassword( void );
  unsigned int getMaxUsers( void );

  void setOperator( User *user );  // it will be more like void addOperator( User *user );
  void setInviteOnly( bool inviteOnly );
  void setTopicProtected( bool topicProtected );
  void setTopic( std::string topic );
  void setPassword( std::string password );
  void setMaxUsers( unsigned int maxUsers );
};

#endif
