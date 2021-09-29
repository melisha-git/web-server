#ifndef RESPONSE_CLASS_HPP
#define RESPONSE_CLASS_HPP

#include "../IHTTP.interface.hpp"
#include "errorResponse.hpp"
#include <sstream>
#include <ctime>
#include <iomanip>

//class Response : public IHTTPMessage {
//private:
//	std::string response_;
//public:
//	Response(const s_startline &startline, const s_headers &headers, const s_bodies &bodies);
//	const std::string &getResponse() const;
//private:
//	virtual void makeStartline();
//	virtual void makeHeaders();
//	virtual void makeBodies();
//};

class Response : public IHTTPMessage {
private:
    std::string response_;
    std::string statusLine_;
    std::string contentLength_;
//    std::string server_;
    std::string date_;
    std::string body_;
    int responseType_;

public:
//    Response(const s_startline &startline, const s_headers &headers, const s_bodies &bodies);
    Response(int responseType);

const std::string &getResponse() const;

private:
    virtual void makeStartline();
    virtual void makeHeaders();
    virtual void makeBodies();
    void createResponse();

    void setAttributes();
    void setStatusLine();
    void setDate();
    void setContentLength();
    void setErrorBody();

    std::string getStatusLine() const;
    std::string getDate() const;
    std::string getBody() const;
    std::string getContentLength() const;

};

#endif
