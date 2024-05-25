#include "ChannelManager.hpp"

ChannelManager::ChannelManager() {
    _channels.clear();
    _command.clear();
}

ChannelManager::~ChannelManager() {
    clearChannels();
}

ChannelManager::ChannelManager( ChannelManager const& src ) {
    *this = src;
}

ChannelManager& ChannelManager::operator=( ChannelManager const& src ) {
    if ( this == &src )
        return ( *this );
    _channels = src._channels;
    return ( *this );
}

Channel* ChannelManager::getChannel( std::string channelName ) {
    if ( _channels.find( channelName ) != _channels.end() )
        return _channels[channelName];
    return NULL;
}

std::map<std::string, Channel*> ChannelManager::getAllChannels() {
    return _channels;
}

void ChannelManager::addChannel( std::string channelName, Channel* channel ) {
    if ( _channels.find( channelName ) == _channels.end() )
        _channels[channelName] = channel;
    else    
        throw ChannelExistsException();
}

void ChannelManager::removeChannel( std::string channelName ) {
    if ( _channels.find( channelName ) != _channels.end() ) {
        delete _channels[channelName];
        _channels.erase( channelName );
    }
    else
        throw ChannelDoesNotExistException();
}

bool ChannelManager::channelExists( std::string channelName ) {
    return ( _channels.find( channelName ) != _channels.end() );
}

User *ChannelManager::getUser( std::string channelName, std::string user ) {
    if ( _channels.find( channelName ) != _channels.end() )
        return _channels[channelName]->getUser( user );
    return NULL;
}

User *ChannelManager::getOperator( std::string channelName ) {
    if ( _channels.find( channelName ) != _channels.end() )
        return _channels[channelName]->getOperator();
    return NULL;
}

bool ChannelManager::isInviteOnly( std::string channelName ) {
    if ( _channels.find( channelName ) != _channels.end() )
        return _channels[channelName]->isInviteOnly();
    return 0;
}

bool ChannelManager::isTopicProtected( std::string channelName ) {
    if ( _channels.find( channelName ) != _channels.end() )
        return _channels[channelName]->isTopicProtected();
    return 0;
}

std::string ChannelManager::getTopic( std::string channelName ) {
    if ( _channels.find( channelName ) != _channels.end() )
        return _channels[channelName]->getTopic();
    return "";
}

std::string ChannelManager::getPassword( std::string channelName ) {
    if ( _channels.find( channelName ) != _channels.end() )
        return _channels[channelName]->getPassword();
    return "";
}

unsigned int ChannelManager::getMaxUsers( std::string channelName ) {
    if ( _channels.find( channelName ) != _channels.end() )
        return _channels[channelName]->getMaxUsers();
    return 0;
}

bool ChannelManager::isValidArg( std::string str ) {
    for ( size_t i = 0; i < str.length(); i++ )
        if ( !isdigit( str[i] ) && !isalpha( str[i] ) )
            return 0;
    return 1;
}

void ChannelManager::clearChannels( void ) {
    for ( std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++ )
        delete it->second;
    _channels.clear();
}
