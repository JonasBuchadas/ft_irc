#include "Server.hpp"

/*
static bool isValidArg( std::string str ) {
  for ( size_t i = 0; i < str.length(); i++ )
    if ( !isdigit( str[i] ) && !isalpha( str[i] ) )
      return 0;
  return 1;
}

std::string Server::checkPasswd( const std::string& message, int fd )
{
    if (message.length() <= 1)
        return "Invalid string\n\0";
    std::string str = message.substr(1, message.find_first_of("\n\r\0", 1) - 1);
    if (!_passlist[fd].empty() && isValidArg(str))
    {
        _passlist[fd] = str;
        return "Password successfully updated\n\0";
    }
    if (isValidArg(str))
    {
        _passlist[fd] = str;
        return "Registered password\n\0";
    }
    else
        return "Password contains invalid characters\n\0";
}

std::string Server::setNickname( const std::string& message, int fd )
{
    if (message.length() <= 1)
        return "Invalid string\n\0";
    std::string str = message.substr(1, message.find_first_of("\n\r\0", 1) - 1);
    for (std::map<int, std::string>::iterator it = _nicklist.begin(); it != _nicklist.end(); it++)
    {
        if (it->first != fd && it->second == str)
            return "Nickname already taken. Nickname not updated\n\0";
    }
    if (!_nicklist[fd].empty() && isValidArg(str))
    {
        _nicklist[fd] = str;
        return "Nickname successfully updated\n\0";
    }
    if (isValidArg(str))
    {
        _nicklist[fd] = str;
        return "Registered your nickname \n\0";
    }
    else
        return "Nickname contains invalid characters\n\0";
}

std::string Server::setUsername( const std::string& message, int fd )
{
    if (message.length() <= 1)
        return "Invalid string\n\0";
    std::string str = message.substr(1, message.find_first_of(" \n\r\0", 1) - 1);
    for (std::map<int, std::string>::iterator it = _namelist.begin(); it != _namelist.end(); it++)
    {
        if (it->first != fd && it->second == str)
            return "Username already taken. Username not updated\n\0";
    }
    if (!_namelist[fd].empty() && isValidArg(str))
    {
        _namelist[fd] = str;
        return "Username successfully updated\n\0";
    }
    if (isValidArg(str))
    {
        _namelist[fd] = str;
        return "Registered your username\n\0";
    }
    else
        return "Username contains invalid characters\n\0";
}

std::string Server::joinChannel( const std::string& message, int fd )
{
    (void)fd;
    return message;
}

std::string Server::partChannel( const std::string& message, int fd )
{
    (void)fd;
    return message;
}

std::string Server::changeModes( const std::string& message, int fd )
{
    (void)fd;
    return message;
}

std::string Server::kickoutUser(const std::string& message, int fd)
{
    (void)fd;
    return message;
}

std::string Server::changeTopic(const std::string& message, int fd)
{
    (void)fd;
    return message;
}

std::string Server::inviteUser(const std::string& message, int fd)
{
    (void)fd;
    return message;
}

std::string Server::directMsg(const std::string& message, int fd)
{
    (void)fd;
    return message;
}


std::string Server::executeCommand(const std::string& command, const std::string& message, int fd) {
    std::map<std::string, CommandFunction>::iterator it = _command.find(command);
    if (it != _command.end()) {
        return (this->*(it->second))(message, fd);
    } else {
        return "";
    }
}

int Server::authenticateUser(int fd)
{
    int pass = 0, nick = 0, user = 0;

    if (!_passlist[fd].empty() && _passlist[fd] == _password)
        pass = 1;
    if (!_nicklist[fd].empty())
        nick = 1;
    if (!_namelist[fd].empty())
        user = 1;

    if (pass && nick && user)
        return 1;
    return 0;
}

void Server::releaseUserInfo(int fd)
{
    if (!_passlist[fd].empty())
        _passlist.erase(fd);
    if (!_nicklist[fd].empty())
        _nicklist.erase(fd);
    if (!_namelist[fd].empty())
        _namelist.erase(fd);
}
*/