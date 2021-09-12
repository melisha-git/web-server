#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include "../IHTTP.interface.hpp"

class Request : IHTTPInterface {
private:
	std::string request_;
public:
	Request(const std::string &request) : request_(request) {
	}
	virtual void makeStartline() {
		std::string	startline = request_.substr(0, request_.find('\n'));
		this->startline_.method = startline.substr(0, startline.find('/') - 1);
		startline = startline.substr(startline.find('/'), startline.find(' ') - startline.find('/'));
		this->startline_.target = startline.substr(0, startline.find(' '));
		this->startline_.version = startline.substr(startline.find(' ') + 1);
		std::cout << this->startline_.method << std::endl;
		std::cout << this->startline_.target << std::endl;
		std::cout << this->startline_.version << std::endl;
	}
	virtual void makeHeaders() {

	}
	virtual void makeBodyes() {

	}
};

#endif
