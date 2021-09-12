#ifndef STRUCTMANAGER_HPP
#define STRUCTMANAGER_HPP

#include <arpa/inet.h>
#include <string>

class StructManager {
private:
	struct sockaddr_in	serverAddress_;
	socklen_t 			size_;
public:
	typedef struct connection_struct {
		int port;
		std::string ip;
		connection_struct(const int &port, const std::string &ip) {
			this->port = port;
			this->ip = ip;
		}
	} connection_struct;
public:
	StructManager(const connection_struct &);

	struct sockaddr_in *getStruct();

	socklen_t	*getSize();
private:
	void updateSize();
};

#endif