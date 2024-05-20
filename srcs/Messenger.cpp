#include "Messenger.hpp"

Messenger::Messenger( int listeningSocket )
{
  _listeningSocket = listeningSocket;
  _recipients.clear();
  _response = "";
  _response.clear();
}

Messenger::~Messenger() {}

Messenger::Messenger( Messenger const &src ) {
  *this = src;
  _recipients = src._recipients;
}

Messenger &Messenger::operator=( Messenger const &src ) {
  if ( this == &src )
    return ( *this );
  return ( *this );
}

void Messenger::respond()
{
  for ( int j = 0; j < (int)_recipients.size(); j++ ) {
    int destFD = _recipients[j];
    if ( destFD != _listeningSocket ) {
      if ( send( destFD, _response.c_str(), _response.size(), 0 ) == -1 )
        perror( "send" );
    }
  }
}

void Messenger::getValidMsg(Authenticator &auth, \
std::vector<pollfd> _pfds, std::map<int, User *> _users,int fd, std::string msg)
{
    size_t start = 0;
    std::string message;

    if (!msg.empty() && msg.find_first_of("\n\r", start) != std::string::npos)
      message = msg.substr(start, msg.find_first_of("\n\r", start));
    else
      message = msg;
    while (!message.empty())
    {
        if (_recipients.empty())
          _recipients.push_back(fd);
        std::string word;
        std::stringstream ss(message);
        ss >> word;
        _response = auth.executeCommand(word, message.substr(word.length()), fd);
        if (_users[fd])
        {
            _recipients.clear();
            for (int i = 0; i < (int)_pfds.size(); i++)
            {
              if (_pfds[i].fd != fd && _users[_pfds[i].fd])
                _recipients.push_back(_pfds[i].fd);
            }
            _response = message + "\n\0";
        }
        start = msg.find_first_of("\n\r\0", start);
        while (start < msg.size() && (msg[start] == '\n' || msg[start] == '\r'))
            start++;
        if (start < msg.size() && msg.find_first_of("\n\r", start) != std::string::npos)
            message = msg.substr(start, msg.find_first_of("\n\r", start) - start);
        else
          break ;
    }
    respond();
    _recipients.clear();
}

void Messenger::tooLargeAMsg( int senderFD )
{
  _recipients.push_back( senderFD );
  _response = "Message will be ignored due to size constraints\n\0";
  respond();
}

void Messenger::LoggedInUser( int senderFD )
{
  _recipients.push_back( senderFD );
  _response = "Successfully logged in!\n\0";
  respond();
}
