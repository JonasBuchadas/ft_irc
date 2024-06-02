
#include <iostream>
#include "CommandFactory.hpp"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <csignal>

bool _stopBot = false;
int mainFD = 3;

std::string awaitInput( int sockfd )
{
  std::string input;
  char buffer[1024];
  int received;
  if ( (received = recv(sockfd, &buffer, sizeof(buffer) - 1, 0)) == -1 )
      return ( "" );
  buffer[received] = 0;
  input = buffer;
  if (received < 1024)
    return input;
  memset(buffer, 0, sizeof(buffer));
  while ( (received = recv(sockfd, &buffer, sizeof(buffer) - 1, MSG_DONTWAIT)) > 0 )
  {
    buffer[received] = 0;
    input += buffer;
    memset(buffer, 0, sizeof(buffer));
  }
  return input;
}

int loginBossBot(int sockfd, char **av)
{
  std::string pass = av[2];
  std::string manager = "PASS " + pass + "\nUSER BossBot\nNICK BossBot\r\n";
  if ( send(sockfd, manager.c_str(), manager.size(), 0) == -1 || awaitInput( sockfd ) == "" )
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

void sigchld_handler( int s ) {
  (void)s;
  _stopBot = true;
  close ( mainFD );
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
    if (sockfd == -1 || loginBossBot(sockfd, av) == -1 )
      return ( -1 );
      
    mainFD = sockfd;
    CommandFactory commands;
    std::signal( SIGINT, sigchld_handler );
    std::signal( SIGQUIT, sigchld_handler );
    std::string fullInput = awaitInput( sockfd );
    while (1)
    {
      if (_stopBot || fullInput.size() <= 1)
        break ;
      std::string input = fullInput;
      int start = 0;
      if ( fullInput.find_first_of( "\n\r" ) != std::string::npos )
        input = fullInput.substr( 0, fullInput.find_first_of( "\n\r" ) );
      start = fullInput.find_first_of( "\n\r" );
      while ( start < (int)fullInput.size() && ( fullInput[start] == '\n' || fullInput[start] == '\r' ) )
          start++;
      while (1)
      {
        std::string sender;
        std::string word;
        if (input.find("!") != std::string::npos)
        {
          input = input.substr(1);
          sender = input.substr(0, input.find("!"));
          int beg = input.find(":");
          if (input[beg + 1])
          {
            std::string end = input.substr(beg + 1);
            word = end.substr(0, end.find(" "));
          }
          if (word == "INVITE" && input.find(":") != std::string::npos)
            input = input.substr(input.find(":") + 1);
          else if (word == "SHOOT" && input.find("#") != std::string::npos)
          {
            input = input.substr(input.find("#"));
            if (input.find(" ") != std::string::npos)
              input = input.substr(0, input.find(" "));
          }
        }
        std::cout << input << std::endl;
        ACommand *cmd = commands.makeCommand( word, input, sender );
        std::string response = cmd->execute();
        delete cmd;
        for (size_t i = 0; i < response.size(); i++) {
          if (response[i] == '\n' && i + 1 < response.size()) {
            response.insert(i + 1, "PRIVMSG " + sender + " :");
            i += 11;
          }
        }
        if ( send(sockfd, response.c_str(), response.size(), 0) == -1)
          return ( -1 );
        if (!fullInput[start])
          break ;
        start = fullInput.find_first_of( "\n\r\0", start );
        while ( start < (int)fullInput.size() && ( fullInput[start] == '\n' || fullInput[start] == '\r' ) )
          start++;
        if ( start < (int)fullInput.size() && fullInput.find_first_of( "\n\r", start ) != std::string::npos )
          input = fullInput.substr( start - 1, fullInput.find_first_of( "\n\r", start ) - start );
        else
          break;
      }
      fullInput = awaitInput( sockfd );
    }
  }
  catch ( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << std::endl;
    return ( -1 );
  }
  return ( 0 );
}

