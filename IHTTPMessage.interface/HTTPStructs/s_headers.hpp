#ifndef S_HEADERS_HPP
#define S_HEADERS_HPP

#include <vector>
#include <string>

struct s_headers {
	std::vector<std::string>	headers;

//	s_headers(const s_headers &other) {
//		*this = other;
//	}

	s_headers &operator=(const s_headers &other) {
		for (const std::string &str : other.headers) {
			this->headers.push_back(str);
		}
		return *this;
	}
};

#endif
