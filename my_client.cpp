
#include "color.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#define  BUFF_SIZE   1024

int		main( int argc, char *argv[]){
	int						client_socket;
	struct sockaddr_in		server_addr;
	char					buff[BUFF_SIZE + 5];

	client_socket = socket(PF_INET, SOCK_STREAM, 0);		// <sys/socket.h>

	if(client_socket == -1) {
		std::cerr << "socket 생성 실패" << '\n';
		return 1;
	}

	std::memset(&server_addr, 0, sizeof(server_addr));	// init
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
		std::cerr << "접속 실패" << '\n';
		return 1;
	}

	std::string		input;
	int i = 0;
	while (true) {
		std::cout << "iter" << ++i << std::endl;
		std::getline(std::cin, input);
		std::cout << "size : " << input.length() + 1 << std::endl;
		write(client_socket, input.c_str(), input.length() + 1); // + 1: NULL까지 포함해서 전송
		// if (send(client_socket, input.c_str(), input.length() + 1, 0) == -1) {
		//     std::cerr << "send 실패" << '\n';
		//     return 1;
		// }
		if (read(client_socket, buff, BUFF_SIZE) == -1) {
			std::cout << "read 실패" << std::endl;
			return 1;
		}
		std::cout << buff << std::endl;
		std::cin.clear();
	}
	close(client_socket);
	system("leaks -q client");
	return 0;
}



/* socket
 * int socket(domain, type, protocol)
 * Return : fd
 */
