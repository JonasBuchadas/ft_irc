
#include <iostream>

#include "Server.hpp"

int main( int ac, char **av ) {
  if ( ac != 3 ) {
    std::cerr << "Error: invalid number of arguments" << std::endl;
    return ( -1 );
  }
  try {
    Server s = Server( av[1], av[2] );
    s.serve();
  } catch ( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << std::endl;
    return ( -1 );
  }
  return ( 0 );
}
