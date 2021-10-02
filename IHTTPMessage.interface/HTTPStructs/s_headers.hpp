#ifndef S_HEADERS_HPP
#define S_HEADERS_HPP

#include <map>
#include <string>

struct s_headers {
	std::map<std::string, std::string>	headers;

//	s_headers(const s_headers &other) {
////		*this = other;
//        headers = other.headers;
//	}
//
//	s_headers() {};
//
//	s_headers &operator=(const s_headers &other) {
////		for (const std::string &str : other.headers) {
////			this->headers.push_back(str);
////		}
////		return *this;
//    headers = other.headers;
//    return *this;
//	}

};

#endif
