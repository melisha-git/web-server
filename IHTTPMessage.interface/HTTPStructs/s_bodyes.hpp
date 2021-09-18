#ifndef S_BODYES_HPP
#define S_BODYES_HPP

#include <vector>
#include <string>

struct s_bodyes {
	std::vector<std::string>	bodyes;

//	s_bodyes(const s_bodyes &other) {
//		*this = other;
//	}

	s_bodyes &operator=(const s_bodyes &other) {
		for (const std::string &str : other.bodyes) {
			this->bodyes.push_back(str);
		}
		return *this;
	}
};

#endif
