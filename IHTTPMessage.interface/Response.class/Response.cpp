#include "Response.class.hpp"

Response::Response(const s_startline &startline, const s_headers &headers, const s_bodyes &bodyes) {
	this->startline_ = startline;
	this->headers_ = headers;
	this->bodyes_ = bodyes;
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