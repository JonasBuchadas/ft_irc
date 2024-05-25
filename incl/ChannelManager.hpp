#pragma once
#ifndef __CHANNELMANAGER_HPP__
#define __CHANNELMANAGER_HPP__

#include <map>
#include <iostream>
#include "Channel.hpp"

class ChannelManager {
    private:
    ChannelManager();
    std::map<std::string, Channel*> _channels;
    
    typedef std::string ( ChannelManager::*CommandFunction )( const std::string&, int fd );
    std::map<std::string, CommandFunction> _command;
    
    public:
    ChannelManager( ChannelManager const& src );
    ChannelManager& operator=( ChannelManager const& src );
    ~ChannelManager();
    
    Channel*                getChannel( std::string channelName );
    std::map<std::string, Channel*> getAllChannels();
    void                    addChannel( std::string channelName, Channel* channel );
    void                    removeChannel( std::string channelName );
    bool                    channelExists( std::string channelName );
    
    User*                   getUser( std::string channelName, std::string user );
    //User*                   getOperator( std::string channelName );

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