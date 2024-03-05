#include <iostream>
#include <cctype>
#include <stdlib.h>

int main(int ac, char **av)
{
	int port;
	std::string password;

	if (ac == 3)
	{
		if (!av[1][0] || !av[2][0])
		{
			std::cerr << "Error: Empty argument" << std::endl;
			return (1);
		}
		for(int i = 0; av[1][i]; i++)
		{
			if (!std::isdigit(av[1][i]))
			{
				std::cerr << "Error: Port is not number" << std::endl;
				return (1);
			}
		}
		port = atoi(av[1]);
		password = av[2];
		std::cout << "OK!" << std::endl;
	}
	else
		std::cerr << "Error: Invalid number of arguments" << std::endl;
}
