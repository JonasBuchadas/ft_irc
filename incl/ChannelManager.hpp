#pragma once
#ifndef __CHANNELMANAGER_HPP__
#define __CHANNELMANAGER_HPP__

#include <iostream>
#include <map>

#include "Channel.hpp"

class ChannelManager {
 private:
  std::map<std::string, Channel*> _channels;

  typedef std::string ( ChannelManager::*CommandFunction )( const std::string&, int fd );
  std::map<std::string, CommandFunction> _command;

 public:
  ChannelManager();
  ChannelManager( ChannelManager const& src );
  ChannelManager& operator=( ChannelManager const& src );
  ~ChannelManager();

  bool channelExists( std::string channelName );

  Channel*                        getChannel( std::string channelName );
  std::map<std::string, Channel*> getAllChannels();
  void                            addChannel( std::string channelName, Channel* channel );
  void                            removeChannel( std::string channelName );

  bool         isUser( std::string channelName, int user );
  bool         isOperator( std::string channelName, int user );
  bool         isInviteOnly( std::string channelName );
  bool         isTopicProtected( std::string channelName );
  std::string  getTopic( std::string channelName );
  std::string  getPassword( std::string channelName );
  unsigned int getMaxUsers( std::string channelName );
  std::string  getChannelModes( std::string channelName );

  void setOperator( std::string channelName, int user );  // it will be more like void addOperator( User *user );
  void setInviteOnly( std::string channelName, bool inviteOnly );
  void setTopicProtected( std::string channelName, bool topicProtected );
  void setTopic( std::string channelName, std::string topic );
  void setPassword( std::string channelName, std::string password );
  void setMaxUsers( std::string channelName, unsigned int maxUsers );

  bool isValidArg( std::string str );

  void clearChannels( void );

  class ChannelExistsException : public std::exception {
   public:
    virtual const char* what() const throw() {
      return "Channel already exists\n\0";
    }
  };

  class ChannelDoesNotExistException : public std::exception {
   public:
    virtual const char* what() const throw() {
      return "Channel does not exist\n\0";
    }
  };
};

#endif
