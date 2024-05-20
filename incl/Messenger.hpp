#pragma once
#ifndef __MESSENGER_HPP__
#define __MESSENGER_HPP__

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

#include <iostream>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>

#include "User.hpp"
#include "Authenticator.hpp"

class Authenticator;

class Messenger {
    private:
        Messenger( Messenger const &src );
        Messenger &operator=( Messenger const &src );

        std::vector<int>      _recipients;
        std::string           _response;
        int                   _listeningSocket;
        
        std::string processMsg( int fd, std::string msg );
        void respond();

        /*
        _command["JOIN"] =  &Server::joinChannel;
        _command["PART"] =  &Server::partChannel;
        _command["MODE"] =  &Server::changeModes;
        _command["KICK"] =  &Server::kickoutUser;
        _command["TOPIC"] = &Server::changeTopic;
        _command["INVITE"] = &Server::inviteUser;
        _command["PRIVMSG"] = &Server::directMsg;
        */

    public:
        Messenger( int listeningSocket );
        ~Messenger();

        void tooLargeAMsg( int senderFD );
        void getValidMsg( Authenticator &auth, std::vector<pollfd> _pfds, \
        std::map<int, User *> _users, int fd, std::string msg );
        void LoggedInUser( int senderFD );
};

#endif
