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
		std::cout << "Start Line = " << startline << std::endl;
		this->startline_.method = startline.substr(0, startline.find('/') - 1);
		startline = startline.substr(startline.find('/'), startline.find(' ') - startline.find('/'));
		this->startline_.target = startline.substr(0, startline.find(' '));
		this->startline_.version = startline.substr(startline.find(' ') + 1);

		std::cout << "Method  " << this->startline_.method << std::endl;
		std::cout << "Target  " << this->startline_.target << std::endl;
		std::cout << "Version " << this->startline_.version << std::endl;
	}
	virtual void makeHeaders() {
		this->headers_.size = 0;
		std::string headers = request_.substr(request_.find('\n') + 1);
		std::string delimiter = "\n";

		size_t pos = 0;
		std::string token;
		while ((pos = headers.find(delimiter)) != std::string::npos) {
			token = headers.substr(0, pos);
			this->headers_.headers.push_back(token);
			std::cout << this->headers_.headers[this->headers_.size++] << std::endl << '*';
			headers.erase(0, pos + delimiter.length());
			if (headers[pos] == '\n' && headers[pos + 1] == '\n')
				break;
		}
	}
	virtual void makeBodyes() {

	}
};

#endif
