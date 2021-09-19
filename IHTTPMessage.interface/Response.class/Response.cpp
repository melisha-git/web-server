#include "Response.class.hpp"

Response::Response(const s_startline &startline, const s_headers &headers, const s_bodyes &bodyes) {
	this->s_startline_ = startline;
	this->s_headers_ = headers;
	this->s_bodyes_ = bodyes;
	makeStartline();
	makeHeaders();
	makeBodyes();
}

void Response::makeStartline() {

}

void Response::makeHeaders() {

}

void Response::makeBodyes() {

}

const std::string &Response::getResponse() const {
	return response_;
}
