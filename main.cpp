#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define ERROR_MSG "Error:\t"
#define DONE_MSG "Done:\t"

int main() {
	std::cout << "\t\tCreate socket\n\n";
	int listen_sock;
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == -1) {
		std::cout << ERROR_MSG << "socket is not created\n";
		exit(0);
	}

	std::cout << DONE_MSG << "socket is created\n\n";
	std::cout << "\t\tBinding\n\n";

	struct sockaddr_in addrs;
	int result = 1;
	addrs.sin_family = AF_INET;
	addrs.sin_port = htons(1112);
	addrs.sin_addr.s_addr = inet_addr("127.0.0.1");

	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &result, sizeof(int));
	socklen_t size = sizeof (addrs);

	result = bind(listen_sock, reinterpret_cast<sockaddr *>(&(addrs)), size);
	if (result == -1) {
		std::cout << ERROR_MSG << "no bind\n\n";
		exit(0);
	}

	std::cout << DONE_MSG << "bind OK :)\n\n";
	std::cout << "\t\tListen\n\n";

	result = listen(listen_sock, 1);
	if (result == -1) {
		std::cout << ERROR_MSG << "no listen\n\n";
		exit(0);
	}

	std::cout << DONE_MSG << "listen OK :)\n\n";
	std::cout << "\t\tAccept\n\n";

	int newsock = accept(listen_sock, reinterpret_cast<sockaddr*>(&(addrs)), &size);
	if (newsock == -1) {
		std::cout << ERROR_MSG << "no accept\n\n";
		exit(0);
	}

	std::cout << "accept OK :)\n\n";

	char buf[1024];
	std::string bu;

	for (;;) {
		memset(buf, 0, 1024);
		result = recv(newsock, buf, 1024, 0);
		write(1, buf, result);

		memset(buf, 0, 1024);
		std::getline(std::cin, bu);
		bu += '\n';
		std::memcmp(bu.c_str(), buf, bu.size());
		send(newsock, buf, bu.size(), 0);
	}

	close(newsock);
	close(listen_sock);
	return 0;
}
