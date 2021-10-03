#include "Request.hpp"

Request::Request(const std::string &request) : request_(request), responseType(0) {
//    isBodies_ = (request_.find("\r\n\r\n") != std::string::npos);

    makeStartline();
    isBodies_ = (request_.find("\r\n\r\n") + 4 != request_.length());
    makeHeaders();
    makeBodies();
    s_headers_.print();
    s_bodies_.print();
}

const s_startline &Request::getStartLine() const {
	return this->s_startline_;
}

const s_headers &Request::getHeaders() const {
	return this->s_headers_;
}

const s_bodies &Request::getBodies() const {
	return this->s_bodies_;
}

void Request::makeStartline() {
	std::string	startline = request_.substr(0, request_.find('\r'));

	size_t endMethod, endTarget;
	endMethod = startline.find(' ');
	endTarget = startline.find_last_of(' ');

	if (endMethod == std::string::npos || endTarget == std::string::npos ||
	endMethod == endTarget)
	{
	    responseType = 400;
        return;
	}

	this->s_startline_.method = startline.substr(0, endMethod);
    if (!s_startline_.isMethodImplemented()) {
        responseType = 501;
        return ;
    }

	if (!s_startline_.isMethodAllowed()) {
	    responseType = 405;
	    return ;
	}

	startline.erase(0, endMethod + 1);

	this->s_startline_.target = startline.substr(0, endTarget - endMethod - 1);
	this->s_startline_.version = startline.substr(startline.find_last_of(' ') + 1);

	if (s_startline_.version.find("HTTP") != 0)
	{
	    responseType = 400;
	    return;
	}
	if (!s_startline_.isVersionCorrect()) {
	    responseType = 505;
	    return ;
	}
	responseType = 200;
}

void Request::makeHeaders() {
    std::vector<std::string> _vecHeaders;

    size_t headersBegin = request_.find("\r\n") + 2;
    size_t headersLength = request_.find("\r\n\r\n") - headersBegin + 2;
    _vecHeaders = splitVector(request_.substr(headersBegin, headersLength), "\r\n");

    auto it = _vecHeaders.cbegin();
    auto ite = _vecHeaders.cend();
    for (;it < ite; it++) {
        this->s_headers_.headers[(*it).substr(0, (*it).find(':'))] = (*it).substr((*it).find(':') + 1);
    }

}

void Request::makeBodies()  {
	if (!isBodies_)
		return;

	std::string bodyBegin = request_.substr(request_.find("\r\n\r\n") + 4);
    std::vector<std::string> vSplit = splitVector(bodyBegin, "\n");

    s_bodies_.bodies = vSplit;
    if (this->s_bodies_.bodies.empty())
		this->s_bodies_.bodies.clear();
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
	if (isBodies_)
		result.push_back(lines.substr(0, pos));
	return result;
}
