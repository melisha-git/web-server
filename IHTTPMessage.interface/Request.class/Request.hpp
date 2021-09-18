#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include "../IHTTP.interface.hpp"

class Request : IHTTPMessage {
private:
	const std::string request_;
public:
	Request(const std::string &request) : request_(request) {
		makeStartline();
		makeHeaders();
		makeBodyes();
	}

	const s_startline &getStartLine() {
		return this->startline_;
	}

	const s_headers &getHeaders() {
		return this->headers_;
	}

	const s_bodyes &getBodyes() {
		return this->bodyes_;
	}

private:
	virtual void makeStartline() {
		std::string	startline = request_.substr(0, request_.find('\n'));

		this->startline_.method = startline.substr(0, startline.find('/') - 1);
		startline.erase(0, startline.find(' ') + 1);
		this->startline_.target = startline.substr(0, startline.find(' '));
		this->startline_.version = startline.substr(startline.find(' ') + 1);
	}
	virtual void makeHeaders() {
		this->headers_.headers = splitVector(request_.substr(request_.find('\n') + 1, request_.find("\n\n") - request_.find('\n')));
	}
	virtual void makeBodyes() {
		std::vector<std::string> vSplit = splitVector(request_ + "\n\n", "\n\n");
		if (vSplit.size() == 1) {
			return;
		}
		//TODO ADD ALL BODYES
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
