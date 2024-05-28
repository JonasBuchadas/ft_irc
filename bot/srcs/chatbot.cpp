
#include <iostream>
#include "BotManager.hpp"
#include "CommandFactory.hpp"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

std::string awaitInput( int sockfd )
{
  char buffer[1024];
  int received;
  while ( (received = recv(sockfd, &buffer, sizeof(buffer) - 1, 0)) <= 0 ) {
    if ( received == -1 )
      return ( "" );
  }
  buffer[received] = 0;
  std::string input(buffer);
  return input;
}

int loginBossBot(int sockfd, char **av)
{
  std::string pass = av[2];
  std::string manager = "PASS " + pass + "\nUSER BossBot\nNICK BossBot\r\n";
  if ( send(sockfd, manager.c_str(), manager.size(), 0) == -1 || awaitInput( sockfd ).size() == 1 )
    return ( -1 );
  return ( 0 );
}

int connectToServer( char *port)
{
  struct addrinfo hints, *res;
  int sockfd;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo("localhost", port, &hints, &res) != 0) {
      std::cerr << "getaddrinfo failed\n";
      return -1;
  }

  if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
      std::cerr << "socket failed\n";
      return -1;
  }

  if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
      std::cerr << "connect failed\n";
      close(sockfd);
      freeaddrinfo(res);
      return -1;
  }

  freeaddrinfo(res);
  return sockfd;
}

int main(int ac, char **av)
{
  if ( ac != 3 )
  {
    std::cerr << "Error: invalid number of arguments" << std::endl;
    std::cerr << "Usage: [PORT] [PASSWORD]" << std::endl;
    return ( -1 );
  }
  (void) av;
  try
  {
    int sockfd = connectToServer( av[1] );
    if (sockfd == -1 || loginBossBot(sockfd, av) == -1 || awaitInput( sockfd ).size() == 1 )
      return ( -1 );
      
    BotManager *botmanager = new BotManager;
    CommandFactory commands;
    while (1)
    {
      std::string input = awaitInput( sockfd );
      std::string sender = input.substr(1, input.find("!") - 1);
      input = input.substr(1);
      if ( input.find(":") != std::string::npos )
      {
        input = input.substr(input.find(":") + 1);
        std::stringstream ss( input );
        std::string word;
        ss >> word;
        ACommand *cmd = commands.makeCommand( word, botmanager, input.substr(word.length()), sender );
        std::string prefix = "PRIVMSG " + sender + " :";
        std::string response = prefix + cmd->execute();
        delete cmd;
        for (size_t i = 0; i < response.size(); ++i) {
          if (response[i] == '\n' && i + 1 < response.size()) {
            response.insert(i + 1, prefix);
            i += prefix.size();
          }
        }
        if ( send(sockfd, response.c_str(), response.size(), 0) == -1)
          return ( -1 );
      }
    }
  }
  catch ( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << std::endl;
    return ( -1 );
  }
  return ( 0 );
}
