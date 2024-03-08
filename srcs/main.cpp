#include <iostream>
#include <cctype>
#include <cstring>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int bindSocket(int port)
{
	int sockfd;
	struct sockaddr_in server_addr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		std::cerr << "Error: failed to create socket" << std::endl;
		return -1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		std::cerr << "Error: failed to bind socket" << std::endl;
		return -1;
	}

	return (sockfd);
}

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
		if (bindSocket(port) != -1)
			std::cout << "OK!" << std::endl;
	}
	else
		std::cerr << "Error: Invalid number of arguments" << std::endl;
}
