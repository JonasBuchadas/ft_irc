#include "Message.hpp"

std::string getFixedParam( int code, std::string param ) {
  (void)param;
  switch ( code ) {
    // Dunno if we need them
    // case ERR_CANNOTSENDTOCHAN:
    //   return ": You're not yet a '" + param + "' channel member";
    // case ERR_UNKNOWNCOMMAND:
    //   return ": Unknown command '" + param + "'";
    // case ERR_KEYSET:
    //   return ": Channel key already defined";
    // case ERR_CANTKILLSERVER:
    //   return ": '" + param + "' command not available";
    // case ERR_USERSDONTMATCH:
    //   return ": Invalid user operation";

    // General Purpose
    case ERR_NOSUCHNICK:
      return " :No such nick/channel";
    // case ERR_TOOMANYTARGETS:
    //   return ": Too many recipients in " + param + " command";
    // case ERR_NORECIPIENT:
    //   return ": Invalid recipient in " + param + " command";
    // case ERR_NONICKNAMEGIVEN:
    //   return ": No nickname given in " + param + " command";
    case ERR_NOTREGISTERED:
      return ":You have not registered";
    case ERR_NEEDMOREPARAMS:
      return "" + param + ":Not enough parameters";

    // Channel
    case RPL_CHANNELMODEIS:
      return param;
    case ERR_NOSUCHCHANNEL:
      return "" + param + ":No such channel";
    case ERR_USERNOTINCHANNEL:
      return "" + param + ":You're not on that channel";
    case ERR_USERONCHANNEL:
      return "" + param + " :is already on channel";
    case ERR_INVITEONLYCHAN:
      return "" + param + ":Cannot join channel (+i)";
    case ERR_BADCHANNELKEY:
      return "" + param + ":Cannot join channel (+k)";
    case ERR_CHANOPRIVSNEEDED:
      return "" + param + " :You're not channel operator";
    case ERR_CHANNELISFULL:
      return "" + param + ":Cannot join channel (+l)";

    // Keyword specific commands
    case RPL_WELCOME:
      return ":Welcome to the server, " + param;
    case ERR_PASSWDMISMATCH:
      return ":Password incorrect";
    case ERR_ALREADYREGISTERED:
      return ":You may not reregister";
    case ERR_ERRONEUSNICKNAME:
      return ":Erroneous nickname";
    case ERR_NICKNAMEINUSE:
      return ":Nickname is already in use";
    case RPL_NOTOPIC:
      return ":No topic is set";
    case RPL_TOPIC:
      return param;
    case ERR_UNKNOWNMODE:
      return param;
    case ERR_NOTEXTTOSEND:
      return ":No text to send";
    case RPL_NAMREPLY:
      return param;

    // Custom Msgs
    case UPD_AUTHELEM:
      return ": " + param + " successfully registered";
    case INVALIDAUTHELEM:
      return ": " + param + " contains invalid characters";
    case ERR_USERNAMEINUSE:
      return ": Username is already in use";
    case ERR_USERNOTFOUND:
      return ": Couldn't find user";
    case ERR_IPNOTFOUND:
      return ": Invalid ip address";
    case ERR_TARGETNOTAUTH:
      return ": Command target not authenticated";
    case ERR_TARGETNOTINCHANNEL:
      return ": Command target not in channel";
    case ERR_TARGETISOPER:
      return ": Command target is already operator";
    case ERR_TARGETNOTOPER:
      return ": Command target is not operator";
    case ERR_TARGETALREADYINV:
      return ": Invitee already invited";
    default:
      return "Unknown error code";
  }
}

std::string genServerMsg( int code, std::string nick, std::string param ) {
  std::ostringstream s;
  s << code;
  std::string scode( s.str() );
  return ":server " + scode + " " + nick + " " + getFixedParam( code, param ) + "\r\n";
}

std::string genUserMsg( User *userinfo, std::string msg ) {
  /* ___Expected_msg_structure___:
  NICK + newNickname
  JOIN + :#channel
  PART + #channel + :Reason parting
  KICK + #channel + targetNickname + :Reason for kick
  INVITE + inviteeNick + #channel
  TOPIC + #channel + :New topic
  MODE + #channel + signal_and_flag + targetNickname
  */

  return ":" + userinfo->getNick() + "!~" + userinfo->getName() + "@* " + msg + "\r\n";
}
