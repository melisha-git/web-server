#include "Request.hpp"

Request::Request(const std::string &request) : request_(request), responseType(0) {
    isBodies_ = (request_.find("\n\n") != std::string::npos);
    makeStartline();
    if (responseType == 200)
        makeHeaders();
    if (responseType == 200)
        makeBodies();
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

    _vecHeaders = splitVector(request_.substr(request_.find('\n') + 1, request_.find("\r\n\n")), "\r'n");

    auto it = _vecHeaders.cbegin();
    auto ite = _vecHeaders.cend();
    for (;it < ite; it++) {
        std::cout << "before - " << (*it) << std::endl;
        this->s_headers_.headers[(*it).substr(0, request_.find(':'))] = (*it).substr(request_.find(':') + 1,
                                                                                     request_.find("\r\n"));
    }
}

void Request::makeBodies()  {
	if (!isBodies_) {
		return;
	}
	std::vector<std::string> vSplit = splitVector(request_ + "\n\n", "\n\n");
	//TODO ADD ALL Bodies
	this->s_bodies_.bodies.push_back(vSplit[1]);
	if (this->s_bodies_.bodies == std::vector<std::string>{""})
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
	if (!isBodies_)
		result.push_back(lines.substr(0, pos));
	return result;
}

//
//std::ostream & operator<<(std::ostream & o, const Request & rhs) {
//    o << rhs.getStartLine().method << std::endl
//      << rhs.getStartLine().target << std::endl
//      << rhs.getStartLine().version << std::endl;
//    return o;
//};
//
//void Request::print() const {
//
//        for(std::map<std::string, std::string>::const_iterator it = this->s_headers_.headers.cbegin();
//        it != this->s_headers_.headers.cend(); ++it)
//            std::cout << (*it).first << " " << (*it).second << "\n";
//
//}