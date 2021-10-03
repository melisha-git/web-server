#ifndef S_HEADERS_HPP
#define S_HEADERS_HPP

#include <map>
#include <string>
#include <iostream>

struct s_headers {
	std::map<std::string, std::string>	headers;

//	s_headers(const s_headers &other) {
////		*this = other;
//        headers = other.headers;
//	}
//
//	s_headers() {};

//	s_headers &operator=(const s_headers &other) {
//        if (this == &other)
//            return *this;
//        headers = other.headers;
//		return *this;
//	}

    void print()
    {
        for (auto const &pair: headers) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
    }
};

#endif
