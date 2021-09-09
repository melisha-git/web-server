#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define ERROR_MSG "ERROR:\t"
#define DONE_MSG "DONE:\t"

int main() {
	std::cout << "\t\tCreate socket\n\n";
	int listen_sock, new_fd;
	fd_set master, read_fds;
	int fdmax;

	FD_ZERO(&master);
	FD_ZERO(&read_fds);

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

	result = listen(listen_sock, 10);
	if (result == -1) {
		std::cout << ERROR_MSG << "no listen\n\n";
		exit(0);
	}

	char buf[1024];
	FD_SET(listen_sock, &master);
	fdmax = listen_sock;
	std::cout << DONE_MSG << "listen OK :)\n\n";
	std::cout << "\t\tBegin server\n\n";
	for (;fdmax;) {
		read_fds = master;
		result = select(fdmax + 1, &read_fds, 0, 0, 0);
		if (result == -1) {
			std::cout << ERROR_MSG << "no select\n\n";
			exit(0);
		}
		for (int i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &read_fds)) {
				if (i == listen_sock) { // Новое соединение
					std::cout << DONE_MSG << "new connect\n\n";
					size = sizeof (addrs);
					new_fd = accept(listen_sock, reinterpret_cast<sockaddr*>(&(addrs)), &size);
					if (new_fd == -1) {
						std::cout << ERROR_MSG << "no accept\n\n";
						exit(0);
					} else {
						FD_SET(new_fd, &master);
						if (new_fd > fdmax)
							fdmax = new_fd;
					}
				} else {
					result = recv(i, buf, 1024, 0);
					if (result <= 0) { // Соединение закрыто или ошибка
						if (result == 0) // Close
							std::cout << i << "\tclose connect\n\n";
						else
							std::cout << ERROR_MSG << "no recv\n\n";
						close(i);
						FD_CLR(i, &master);
					} else {
						for(int j = 0; j <= fdmax; j++) {
							if (FD_ISSET(j, &master)) {
								if (j != listen_sock && j != i) {
									result = send(j, buf, result, 0);
									if (result == -1) {
										std::cout << ERROR_MSG << "no send\n\n";
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return 0;
}
