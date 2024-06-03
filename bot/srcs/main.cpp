
#include <iostream>
#include "Chatbot.hpp"

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
    Chatbot bot;
    bot.listeningLoop( av );
  }
  catch ( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << std::endl;
    return ( -1 );
  }
  return ( 0 );
}

