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

bool ChannelManager::channelExists( std::string channelName ) {
    return ( _channels.find( channelName ) != _channels.end() );
}

Channel* ChannelManager::getChannel( std::string channelName ) {
    if ( channelExists( channelName ) )
        return _channels[channelName];
    return NULL;
}

std::map<std::string, Channel*> ChannelManager::getAllChannels() {
    return _channels;
}

void ChannelManager::addChannel( std::string channelName, Channel* channel ) {
    if ( !channelExists( channelName ) )
        _channels[channelName] = channel;
    else    
        throw ChannelExistsException();
}

void ChannelManager::removeChannel( std::string channelName ) {
    if ( channelExists( channelName ) ) {
        delete _channels[channelName];
        _channels.erase( channelName );
    }
    else
        throw ChannelDoesNotExistException();
}

User *ChannelManager::getUser( std::string channelName, std::string user ) {
    if ( channelExists( channelName ) )
        return _channels[channelName]->getUser( user );
    return NULL;
}

User *ChannelManager::getOperator( std::string channelName ) {
    if ( channelExists( channelName ) )
        return _channels[channelName]->getOperator();
    return NULL;
}

bool ChannelManager::isInviteOnly( std::string channelName ) {
    if ( channelExists( channelName ) )
        return _channels[channelName]->isInviteOnly();
    return 0;
}

bool ChannelManager::isTopicProtected( std::string channelName ) {
    if ( channelExists( channelName ) )
        return _channels[channelName]->isTopicProtected();
    return 0;
}

std::string ChannelManager::getTopic( std::string channelName ) {
    if ( channelExists( channelName ) )
        return _channels[channelName]->getTopic();
    return "";
}

std::string ChannelManager::getPassword( std::string channelName ) {
    if ( channelExists( channelName ) )
        return _channels[channelName]->getPassword();
    return "";
}

unsigned int ChannelManager::getMaxUsers( std::string channelName ) {
    if ( channelExists( channelName ) )
        return _channels[channelName]->getMaxUsers();
    return 0;
}

void ChannelManager::setOperator( std::string channelName, User* user ) { // Placeholder function
    if ( channelExists( channelName ) )
        _channels[channelName]->setOperator( user );
}

void ChannelManager::setInviteOnly( std::string channelName, bool inviteOnly ) {
    if ( channelExists( channelName ) )
        _channels[channelName]->setInviteOnly( inviteOnly );
}

void ChannelManager::setTopicProtected( std::string channelName, bool topicProtected ) {
    if ( channelExists( channelName ) )
        _channels[channelName]->setTopicProtected( topicProtected );
}

void ChannelManager::setTopic( std::string channelName, std::string topic ) {
    if ( channelExists( channelName ) )
        _channels[channelName]->setTopic( topic );
}

void ChannelManager::setPassword( std::string channelName, std::string password ) {
    if ( channelExists( channelName ) )
        _channels[channelName]->setPassword( password );
}

void ChannelManager::setMaxUsers( std::string channelName, unsigned int maxUsers ) {
    if ( channelExists( channelName ) )
        _channels[channelName]->setMaxUsers( maxUsers );
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
