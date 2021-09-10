#include "Server.class/Server.hpp"

int main() {
	Server server(Server::connection_struct{1111, "127.0.0.1"});
	server.start();
	return 0;
}
