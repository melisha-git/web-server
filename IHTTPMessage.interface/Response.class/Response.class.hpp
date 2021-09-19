#ifndef RESPONSE_CLASS_HPP
#define RESPONSE_CLASS_HPP

#include "../IHTTP.interface.hpp"

class Response : public IHTTPMessage {
private:
	std::string response_;
public:
	Response(const s_startline &startline, const s_headers &headers, const s_bodyes &bodyes);
	const std::string &getResponse() const;
private:
	virtual void makeStartline();
	virtual void makeHeaders();
	virtual void makeBodyes();
};

#endif
