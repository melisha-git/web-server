#ifndef S_BODIES_HPP
#define S_BODIES_HPP

#include <vector>
#include <string>

struct s_bodies {
	std::vector<std::string>	bodies;

//	s_bodies(const s_bodies &other) {
//		*this = other;
//	}

	s_bodies &operator=(const s_bodies &other) {
		for (const std::string &str : other.bodies) {
			this->bodies.push_back(str);
		}
		return *this;
	}
};

#endif
