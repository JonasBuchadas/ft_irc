#include "Message.hpp"

std::string getFixedParam( int code, std::string param ) {
  (void)param;
  switch ( code ) {
    // Dunno if we need them
    case ERR_CANNOTSENDTOCHAN:
      return ": You're not yet a '" + param + "' channel member";
    case ERR_UNKNOWNCOMMAND:
      return ": Unknwon command '" + param + "'";
    case ERR_KEYSET:
      return ": Channel key already defined";
    case ERR_CANTKILLSERVER:
      return ": '" + param + "' command not available";
    case ERR_USERSDONTMATCH:
      return ": Invalid user operation";

    // General Purpose
    case ERR_NOSUCHNICK:
      return ": Invalid nickname in " + param + " command";
    case ERR_TOOMANYTARGETS:
      return ": Too many recipients in " + param + " command";
    case ERR_NORECIPIENT:
      return ": Invalid recipient in " + param + " command";
    case ERR_NONICKNAMEGIVEN:
      return ": No nickname given in " + param + " command";
    case ERR_NOTREGISTERED:
      return ": " + param + " command reserved to authenticated users";
    case ERR_NEEDMOREPARAMS:
      return ": " + param + " command lacks some parameters";

    // Channel
    case ERR_NOSUCHCHANNEL:
      return ": Invalid channel name in " + param + " command";
    case ERR_USERNOTINCHANNEL:
      return ": Your are not a member of channel '" + param + "'";
    case ERR_USERONCHANNEL:
      return ": '" + param + "' already in the channel";
    case ERR_INVITEONLYCHAN:
      return ": '" + param + "' channel is invite only";
    case ERR_BADCHANNELKEY:
      return ": Incorrect channel access key";
    case ERR_CHANOPRIVSNEEDED:
      return ": " + param + " command only allowed to channel operators";

    // Keyword specific commands
    case RPL_WELCOME:
      return ": Successfully logged in!";
    case ERR_PASSWDMISMATCH:
      return ": Incorrect password";
    case ERR_ALREADYREGISTERED:
      return ": user is already authenticated";
    case ERR_ERRONEUSNICKNAME:
      return ": Nickname contains invalid characters";
    case ERR_NICKNAMEINUSE:
      return ": Nickname already taken";
    case RPL_NOTOPIC:
      return ": Channel has no set topic";
    case RPL_TOPIC:
      return ": Channel topic set to '" + param + "'";
    case ERR_UNKNOWNMODE:
      return ": Unknown flag '" + param + "' in MODE command";
    case ERR_NOTEXTTOSEND:
      return ": Message content not provided";
    default:
      return "Unknown error code";
  }
}

std::string genServerMsg( int code, std::string param ) {
  std::ostringstream s;
  s << code;
  std::string scode( s.str() );
  return ":server " + scode + " * " + getFixedParam( code, param ) + "\n";
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

  return ":" + userinfo->getNick() + "!~" + userinfo->getName() + "@* " + msg + "\n";
}
