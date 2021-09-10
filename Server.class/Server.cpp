#include "Server.hpp"

Server::Server(const Server::connection_struct &connectionStruct) : error_(1), structManager(connectionStruct) {
	socketInit(connectionStruct);
	socketBind();
	socketListening();
}

void Server::start() {
	Debug::Log("Start server");

	selectHelper.setMaster(socket_);

	for (;selectHelper.getCount();) {
		selectHelper.makeSelect();
		FDBeginner();
	}
}

void Server::FDBeginner() {
	for (int i = 0; i <= selectHelper.getCount(); i++) {
		if (selectHelper.isUtils(i)) {
			if (i == socket_) {
				doAccept();
			} else {
				doRead(i);
			}
		}
	}
}

void Server::doAccept() {
	int acceptFD;
	Debug::Log("new connect");
	acceptFD = accept(socket_, reinterpret_cast<sockaddr*>(structManager.getStruct()), structManager.getSize());
	if (acceptFD == -1) {
		throw Server::ServerException("no accept");
	} else {
		selectHelper.setMaster(acceptFD);
	}
}

void Server::doRead(int &socket) {
	char buf[1024];
	error_ = recv(socket, buf, 1024, 0);
	if (error_ <= 0) {
		if (error_ == 0)
			Debug::Log(std::to_string(socket) + "\tclose connect", true);
		else
			Debug::Log("no read", true);
		close(socket);
		selectHelper.deleteMaster(socket);
	} else {
		doWrite(socket, buf);
	}
}

void Server::doWrite(int &socket, char *buf) {
	for(int j = 0; j <= selectHelper.getCount(); j++) {
		if (selectHelper.isMaster(j)) {
			if (j != socket_ && j != socket) {
				error_ = send(j, buf, error_, 0);
				if (error_ == -1) {
					Debug::Log("no write", true);
				}
			}
		}
	}
}

void Server::socketBind() {
	setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &error_, sizeof(int));

	error_ = bind(socket_, reinterpret_cast<sockaddr *>((structManager.getStruct())), *structManager.getSize());
	if (error_ == -1) {
		throw Server::ServerException("no bind");
	}
}

void Server::socketListening() {
	error_ = listen(socket_, 10);
	if (error_ == -1) {
		throw Server::ServerException("no listen");
	}
}

void Server::socketInit(const Server::connection_struct &connectionStruct) {
	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_ == -1) {
		throw Server::ServerException("no socket");
	}
}
