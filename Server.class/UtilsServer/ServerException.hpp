#ifndef SERVEREXCEPTION_HPP
#define SERVEREXCEPTION_HPP

#include <exception>
#include <string>

class ServerException : std::exception {
	virtual const char* what() const throw();
public:
	ServerException(const std::string &log);
private:
	std::string logLine_;
};

#endif
