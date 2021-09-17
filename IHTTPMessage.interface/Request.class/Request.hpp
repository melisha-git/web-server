#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include "../IHTTP.interface.hpp"

class Request : IHTTPInterface {
private:
	const std::string request_;
public:
	Request(const std::string &request) : request_(request) {
	}
	virtual void makeStartline() {
		std::string	startline = request_.substr(0, request_.find('\n'));

		this->startline_.method = startline.substr(0, startline.find('/') - 1);
		startline.erase(0, startline.find(' ') + 1);
		this->startline_.target = startline.substr(0, startline.find(' '));
		this->startline_.version = startline.substr(startline.find(' ') + 1);

		std::cout << "Method  " << this->startline_.method << std::endl;
		std::cout << "Target  " << this->startline_.target << std::endl;
		std::cout << "Version " << this->startline_.version << std::endl;
	}
	virtual void makeHeaders() {
		this->headers_.headers = splitVector(request_.substr(request_.find('\n') + 1, request_.find("\n\n") - request_.find('\n') - 1));
		for (const std::string &s : this->headers_.headers) {
			std::cout << s << std::endl;
		}
	}
	virtual void makeBodyes() {
		std::vector<std::string> vSplit = splitVector(request_ + "\n\n", "\n\n");
		if (vSplit.size() == 1) {
			std::cout << "{" << vSplit[0] << "}" << std::endl;
			return;
		}
		this->bodyes_.bodyes.push_back(vSplit[1]);
	}

private:
	std::vector<std::string>	splitVector(std::string lines, std::string delimiter = "\n") {
		std::vector<std::string>	result;

		std::string token;
		for (size_t pos = lines.find(delimiter); pos != std::string::npos; pos = lines.find(delimiter)) {
			token = lines.substr(0, pos);
			result.push_back(token);
			lines.erase(0, pos + delimiter.length());
		}
		return result;
	}
};

#endif
