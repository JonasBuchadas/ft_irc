#include "Commands.hpp"
#include "Server.hpp"

Commands::Commands(Server &server) : _server(server)
{
    _passlist.clear();
    _nicklist.clear();
    _namelist.clear();
    _command.clear();
    _command["PASS"] =  &Commands::checkPasswd;
    _command["NICK"] =  &Commands::setNickname;
    _command["USER"] =  &Commands::setUsername;
    _command["JOIN"] =  &Commands::joinChannel;
    _command["PART"] =  &Commands::partChannel;
    _command["MODE"] =  &Commands::changeModes;
    _command["KICK"] =  &Commands::kickoutUser;
    _command["TOPIC"] = &Commands::changeTopic;
    _command["INVITE"] = &Commands::inviteUser;
    _command["PRIVMSG"] = &Commands::directMsg;
}

Commands::~Commands() {}

Commands::Commands( Commands const &src ) : _server(src._server) {
  *this = src;
}

Commands &Commands::operator=( Commands const &src ) {
  if ( this == &src )
    return ( *this );
  _command = src._command;
  return ( *this );
}


static bool isValidArg( std::string str ) {
  for ( size_t i = 0; i < str.length(); i++ )
    if ( !isdigit( str[i] ) && !isalpha( str[i] ) )
      return 0;
  return 1;
}

std::string Commands::checkPasswd( const std::string& message, int fd )
{
    std::string resp;

    if (message.length() <= 1)
    {
        resp = "Invalid string\n\0";
        return resp;
    }
    std::string str = message.substr(1, message.find_first_of("\n\r\0", 1) - 1);
    if (!_passlist[fd].empty() && isValidArg(str))
    {
        _passlist[fd] = str;
        resp = "Password successfully updated\n\0";
        return resp;
    }
    if (isValidArg(str))
    {
        _passlist[fd] = str;
        resp = "Registered password\n\0";
    }
    else
        resp = "Password contains invalid characters\n\0";
    return resp;
}

std::string Commands::setNickname( const std::string& message, int fd )
{
    std::string resp;

    if (message.length() <= 1)
    {
        resp = "Invalid string\n\0";
        return resp;
    }
    std::string str = message.substr(1, message.find_first_of("\n\r\0", 1) - 1);
    if (!_nicklist[fd].empty() && isValidArg(str))
    {
        std::map<int, User*> users = _server.getUsers();
        for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
        {
            if (it->first != fd && it->second->getNick() == str)
            {
                resp = "Nickname already taken\n\0";
                return resp;
            }
        }
        _nicklist[fd] = str;
        resp = "Nickname successfully updated\n\0";
        return resp;
    }
    if (isValidArg(str))
    {
        _nicklist[fd] = str;
        resp = "Registered your nickname \n\0";
    }
    else
        resp = "Nickname contains invalid characters\n\0";
    return resp;
}

std::string Commands::setUsername( const std::string& message, int fd )
{
    std::string resp;

    if (message.length() <= 1)
    {
        resp = "Invalid string\n\0";
        return resp;
    }
    std::string str = message.substr(1, message.find_first_of("\n\r\0", 1) - 1);
    if (!_namelist[fd].empty() && isValidArg(str))
    {
        std::map<int, User*> users = _server.getUsers();
        for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); it++)
        {
            if (it->first != fd && it->second->getName() == str)
            {
                resp = "Username already taken\n\0";
                return resp;
            }
        }
        _namelist[fd] = str;
        resp = "Username successfully updated\n\0";
        return resp;
    }
    if (isValidArg(str))
    {
        _namelist[fd] = str;
        resp = "Registered your username\n\0";
    }
    else
        resp = "Username contains invalid characters\n\0";
    return resp;
}

std::string Commands::joinChannel( const std::string& message, int fd )
{
    (void)fd;
    return message;
}

std::string Commands::partChannel( const std::string& message, int fd )
{
    (void)fd;
    return message;
}

std::string Commands::changeModes( const std::string& message, int fd )
{
    (void)fd;
    return message;
}

std::string Commands::kickoutUser(const std::string& message, int fd)
{
    (void)fd;
    return message;
}

std::string Commands::changeTopic(const std::string& message, int fd)
{
    (void)fd;
    return message;
}

std::string Commands::inviteUser(const std::string& message, int fd)
{
    (void)fd;
    return message;
}

std::string Commands::directMsg(const std::string& message, int fd)
{
    (void)fd;
    return message;
}


std::string Commands::executeCommand(const std::string& command, const std::string& message, int fd) {
    std::map<std::string, CommandFunction>::iterator it = _command.find(command);
    if (it != _command.end()) {
        return (this->*(it->second))(message, fd);
    } else {
        return "Unknown command\n\0";
    }
}

int Commands::authenticateUser(int fd)
{
    int pass = 0, nick = 0, user = 0;

    if (!_passlist[fd].empty() && _passlist[fd] == _server.getPass())
        pass = 1;
    if (!_nicklist[fd].empty())
        nick = 1;
    if (!_namelist[fd].empty())
        user = 1;

    if (pass && nick && user)
        return 1;
    return 0;
}

void Commands::releaseUserInfo(int fd)
{
    if (!_passlist[fd].empty())
        _passlist.erase(fd);
    if (!_nicklist[fd].empty())
        _nicklist.erase(fd);
    if (!_namelist[fd].empty())
        _namelist.erase(fd);
}