#ifndef S_STARTLINE_HPP
#define S_STARTLINE_HPP

#include <string>

struct s_startline {
	std::string method;
	std::string target;
	std::string version;

//	s_startline(const s_startline &other) {
//		*this = other;
//	}

	s_startline &operator=(const s_startline &other) {
		this->method = other.method;
		this->target = other.target;
		this->version = other.version;
		return *this;
	}
};

#endif
