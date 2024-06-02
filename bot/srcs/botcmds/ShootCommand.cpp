#include "botcmds/ShootCommand.hpp"

ShootCommand::ShootCommand( std::string args, std::string nick ) : ACommand( "SHOOT", args, nick ) {}

ShootCommand::~ShootCommand() {
}

ShootCommand::ShootCommand( ShootCommand const &src ) : ACommand() {
  *this = src;
}

ShootCommand &ShootCommand::operator=( ShootCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

std::string ShootCommand::execute() const {
  return "NAMES " + _args + "\n";
}
