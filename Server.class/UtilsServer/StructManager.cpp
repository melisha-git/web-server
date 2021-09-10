#include "StructManager.hpp"

StructManager::StructManager(const connection_struct &connectionStruct) {
	serverAddress_.sin_family = AF_INET;
	serverAddress_.sin_port = htons(connectionStruct.port);
	serverAddress_.sin_addr.s_addr = inet_addr(connectionStruct.ip.c_str());
}

struct sockaddr_in *StructManager::getStruct() {
	return &serverAddress_;
}

socklen_t *StructManager::getSize()  {
	this->updateSize();
	return &size_;
}

void StructManager::updateSize() {
	size_ = sizeof (serverAddress_);
}