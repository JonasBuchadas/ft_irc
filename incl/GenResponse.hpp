#pragma once
#ifndef __GENRESPONSE_HPP__
#define __GENRESPONSE_HPP__

#include <sstream>
#include <string>
#include "User.hpp"

// Dunno if we need them
#define ERR_CANNOTSENDTOCHAN 404          // Use when: user sends a message to a channel for which he is only invited
#define ERR_UNKNOWNCOMMAND 421            // Use when: receiving an unknown command
#define ERR_KEYSET 467                    // Use when: setting a channel key when channel already has a key
#define ERR_CANTKILLSERVER 483            // Use when: received A KILL command
#define ERR_USERSDONTMATCH 502            // Use when: user tries to change the userinfo of another user

// General Purpose
#define ERR_NOSUCHNICK 401                // Use when: nickname given to command doesn't exist
#define ERR_TOOMANYTARGETS 407            // Use when: too many recipients are given to a command
#define ERR_NORECIPIENT 411               // Use when: no recipient is given to a command that expects it
#define ERR_NONICKNAMEGIVEN 431           // Use when: no nickname is given to a command that expects it
#define ERR_NOTREGISTERED 451             // Use when: getting a command not usable by an unauthenticated user
#define ERR_NEEDMOREPARAMS 461            // Use when: received command lacks parameters

// Channel
#define ERR_NOSUCHCHANNEL 403             // Use when: received channel name doesn't exist
#define ERR_USERNOTINCHANNEL 441          // Use when: a user sends a message to a channel he is not a member of
#define ERR_USERONCHANNEL 443             // Use when: inviting a user to a channel he is already on
#define ERR_INVITEONLYCHAN 473            // Use when: user tries to join invite only channel
#define ERR_BADCHANNELKEY 475             // Use when: user tries to join a key-needed-channel with an invalid key or no key
#define ERR_CHANOPRIVSNEEDED 482          // Use when: regular user tries to use a command only allowed to channel operators

// Authentication
#define RPL_WELCOME 1                     // Use when: login is successful

// PASS Cmd
#define ERR_PASSWDMISMATCH 464            // Use when: getting the server password wrong

// USER cmd
#define ERR_ALREADYREGISTERED 462         // Use when: received USER command by an already authenticated user

// NICK Cmd
#define ERR_ERRONEUSNICKNAME 432          // Use when: nickname to (re)place is invalid
#define ERR_NICKNAMEINUSE 433             // Use when: nickname to (re)place is already taken

// TOPIC Cmd
#define RPL_NOTOPIC 331                   // Use when: viewing channel topic when topic is empty
#define RPL_TOPIC 332                     // Use when: topic change / addition is successful

// MODE Cmd
#define ERR_UNKNOWNMODE 472               // Use when: MODE has an unknown mode flag

// PRIVMSG Cmd
#define ERR_NOTEXTTOSEND 412              // Use when: the PRIVMSG has no message



template <typename T, typename C>
std::string getFixedParam(T type, C command)
{
    (void)type;
    (void)command;
    return "Unknown parameter or command type\n\r";
}

template <typename P>
std::string getFixedParam(int code, P param)
{
    (void) param;
    switch (code)
    {
    // Dunno if we need them
    case ERR_CANNOTSENDTOCHAN:
        return ": You're not yet a '" + param + "' channel member\n\0";
    case ERR_UNKNOWNCOMMAND:
        return ": Unknwon command '" + param + "'\n\0";
    case ERR_KEYSET:
        return ": Channel key already defined\n\0";
    case ERR_CANTKILLSERVER:
        return ": '" + param + "' command not available\n\0";
    case ERR_USERSDONTMATCH:
        return ": Invalid user operation\n\0";

    // General Purpose
    case ERR_NOSUCHNICK:
        return ": Invalid nickname in " + param + " command\n\0";
    case ERR_TOOMANYTARGETS:
        return ": Too many recipients in " + param + " command\n\0";
    case ERR_NORECIPIENT:
        return ": Invalid recipient in " + param + " command\n\0";
    case ERR_NONICKNAMEGIVEN:
        return ": No nickname given in " + param + " command\n\0";
    case ERR_NOTREGISTERED:
        return ": " + param + " command reserved to authenticated users\n\0";
    case ERR_NEEDMOREPARAMS:
        return ": " + param + " command lacks some parameters\n\0";

    // Channel
    case ERR_NOSUCHCHANNEL:
        return ": Invalid channel name in " + param + " command\n\0";
    case ERR_USERNOTINCHANNEL:
        return ": Your are not a member of channel '" + param + "'\n\0";
    case ERR_USERONCHANNEL:
        return ": '" + param + "' already in the channel\n\0";
    case ERR_INVITEONLYCHAN:
        return ": '" + param + "' channel is invite only\n\0";
    case ERR_BADCHANNELKEY:
        return ": Incorrect channel access key\n\0";
    case ERR_CHANOPRIVSNEEDED:
        return ": " + param + " command only allowed to channel operators\n\0";

    // Keyword specific commands
    case RPL_WELCOME:
        return ": Successfully logged in!\n\0";
    case ERR_PASSWDMISMATCH:
        return ": Incorrect password\n\0";
    case ERR_ALREADYREGISTERED:
        return ": user is already authenticated\n\0";
    case ERR_ERRONEUSNICKNAME:
        return ": Nickname contains invalid characters\n\0";
    case ERR_NICKNAMEINUSE:
        return ": Nickname already taken\n\0";
    case RPL_NOTOPIC:
        return ": Channel has no set topic\n\0";
    case RPL_TOPIC:
        return ": Channel topic set to '" + param + "'\n\0";
    case ERR_UNKNOWNMODE:
        return ": Unknown flag '" + param "' in MODE command\n\0";
    case ERR_NOTEXTTOSEND:
        return ": Message content not provided\n\0";
    default:
        return "Unknown error code";
    }
}


template <typename T, typename C>
std::string genMsg(T sender, C param)
{
    (void)sender;
    (void) param;
    return "Unknown sender or param type";
}

template <typename C>
std::string genMsg(int code, C param)
{
    std::ostringstream s;
    s << code;
    std::string scode(s.str());
    return ":server " + scode + " * " + getFixedParam(code, param);
}


template <typename C>
std::string genMsg(User *userinfo, std::string msg)
{
    /* ___Expected_msg_structure___:
    NICK + newNickname
    JOIN + :#channel
    PART + #channel + :Reason parting
    KICK + #channel + targetNickname + :Reason for kick
    INVITE + inviteeNick + #channel
    TOPIC + #channel + :New topic
    MODE + #channel + signal_and_flag + targetNickname
    */

    return ":" + userinfo->getNick() + "!~" + userinfo->getName() + "@* " + msg;
}

#endif
