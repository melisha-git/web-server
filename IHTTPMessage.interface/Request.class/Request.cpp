#include "Request.hpp"

Request::Request(const std::string &request) : request_(request) {
	isBodyes_ = (request_.find("\n\n") != std::string::npos);
	makeStartline();
	makeHeaders();
	makeBodyes();
}

const s_startline &Request::getStartLine() const {
	return this->s_startline_;
}

const s_headers &Request::getHeaders() const {
	return this->s_headers_;
}

const s_bodyes &Request::getBodyes() const {
	return this->s_bodyes_;
}

void Request::makeStartline() {
	std::string	startline = request_.substr(0, request_.find('\n'));

	this->s_startline_.method = startline.substr(0, startline.find('/') - 1);
	startline.erase(0, startline.find(' ') + 1);
	this->s_startline_.target = startline.substr(0, startline.find(' '));
	this->s_startline_.version = startline.substr(startline.find(' ') + 1);
}

void Request::makeHeaders() {
	this->s_headers_.headers = splitVector(request_.substr(request_.find('\n') + 1, request_.find("\n\n") - request_.find('\n')));
}

void Request::makeBodyes()  {
	if (!isBodyes_) {
		return;
	}
	std::vector<std::string> vSplit = splitVector(request_ + "\n\n", "\n\n");
	//TODO ADD ALL BODYES
	this->s_bodyes_.bodyes.push_back(vSplit[1]);
	if (this->s_bodyes_.bodyes == std::vector<std::string>{""})
		this->s_bodyes_.bodyes.clear();
}

std::vector<std::string> Request::splitVector(std::string lines, const std::string &delimiter) const  {
	std::vector<std::string>	result;

	std::string token;
	size_t pos = lines.find(delimiter);
	for (; pos != std::string::npos; pos = lines.find(delimiter)) {
		token = lines.substr(0, pos);
		result.push_back(token);
		lines.erase(0, pos + delimiter.length());
	}
	if (!isBodyes_)
		result.push_back(lines.substr(0, pos));
	return result;
}