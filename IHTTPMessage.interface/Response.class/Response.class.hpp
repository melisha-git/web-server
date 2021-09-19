#ifndef RESPONSE_CLASS_HPP
#define RESPONSE_CLASS_HPP

#include "../IHTTP.interface.hpp"

class Response : public IHTTPMessage {
public:
	Response(const s_startline &startline, const s_headers &headers, const s_bodyes &bodyes);

private:
	virtual void makeStartline();
	virtual void makeHeaders();
	virtual void makeBodyes();
};

#endif
