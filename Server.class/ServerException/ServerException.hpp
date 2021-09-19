#ifndef SERVEREXCEPTION_HPP
#define SERVEREXCEPTION_HPP

#include <exception>
#include <string>

class ServerException : std::exception {
	virtual const char* what() const throw();
public:
	explicit ServerException(const std::string &);
private:
	std::string logLine_;
};

#endif
