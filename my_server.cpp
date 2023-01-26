#include "color.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#define  BUFF_SIZE   1024

int   main(void) {

	int						server_socket;
	struct sockaddr_in		server_addr;
	server_socket  = socket(PF_INET, SOCK_STREAM, 0);
	if(server_socket == -1) {
		std::cerr <<  "server socket 생성 실패" << '\n';
		return 1;
	}
	std::memset( &server_addr, 0, sizeof( server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4000);		// ?
	server_addr.sin_addr.s_addr= htonl(INADDR_ANY);

	if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		std::cerr << "bind() 실행 에러" << '\n';
		return 1;
	}
	else if(listen(server_socket, 5) == -1){
		std::cerr <<  "listen() 실행 실패"<< '\n';
		return 1;
	}

	int						client_socket;
	socklen_t   			client_addr_size;
	struct sockaddr_in   	client_addr;
	char					buff_rcv[BUFF_SIZE + 5];
	char   					buff_snd[BUFF_SIZE + 5];
	while(true) {
		client_addr_size = sizeof(client_addr);
		client_socket = ::accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
		if (client_socket == -1) {
			std::cerr << "클라이언트 연결 수락 실패" << '\n';
			return 1;
		}
		read (client_socket, buff_rcv, BUFF_SIZE);
		std::cout << BOLDCYAN << "Receive : " 
				  << RESET << buff_rcv << std::endl;
		// const std::string& tmp(buff_snd);
		// send(client_socket, tmp.c_str(), tmp.length() + 1, 0);
		sprintf(buff_snd, "%s <= len : %lu", buff_rcv, strlen(buff_rcv));
		write(client_socket, buff_snd, strlen(buff_snd) + 1); // +1: NULL까지 포함해서 전송
		close(client_socket);
	}
}

// https://badayak.com/entry/C언어-소켓-생성-함수-socket
