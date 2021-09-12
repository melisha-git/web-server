#ifndef S_HEADERS_HPP
#define S_HEADERS_HPP

#include <vector>
#include <string>

struct s_headers {
	std::vector<std::string>	request_headers;
	std::vector<std::string>	main_headers;
	std::vector<std::string>	entity_headers;
};

#endif
