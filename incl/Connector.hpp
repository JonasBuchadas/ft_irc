#pragma once
#ifndef __CONNECTOR_HPP__
#define __CONNECTOR_HPP__

#include <iostream>
#include <map>
#include <vector>
#include <iostream>

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "User.hpp"
#include "Authenticator.hpp"
#include "Messenger.hpp"

class User;
class Server;
class Messenger;
class Authenticator;

class Connector {
    private:
        Server &_server;
        std::vector<pollfd>  _pfds;

        Connector( Connector const &src );
        Connector &operator=( Connector const &src );

        void addToPfds( int fd );
        int  delFromPfds( int fd );

        void clearUsers();
        std::map<int, User *> _users;
        Authenticator         _authenticator;
        /*
        _users.clear();
        _recipients.clear();
        _command["JOIN"] =  &Server::joinChannel;
        _command["PART"] =  &Server::partChannel;
        _command["MODE"] =  &Server::changeModes;
        _command["KICK"] =  &Server::kickoutUser;
        _command["TOPIC"] = &Server::changeTopic;
        _command["INVITE"] = &Server::inviteUser;
        _command["PRIVMSG"] = &Server::directMsg;
        */

    public:
        Connector(Server &server);
        ~Connector();
        void initListener();
        void monitorChanges( int stopServer );
        
        std::string executeCommand( const std::string& command, const std::string& message, int fd );
        std::string getPass( int fd );
        std::string getNick( int fd );
        std::string getUser( int fd );
        int authenticateUser( std::string password, int fd );
        void releaseUserInfo( int fd );

};

#endif
