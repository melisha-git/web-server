#ifndef RESPONSE_CLASS_HPP
#define RESPONSE_CLASS_HPP

#include "../IHTTP.interface.hpp"
#include "errorResponse.hpp"
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <unistd.h>

class Response : public IHTTPMessage {
private:
    std::string response_;
    std::string statusLine_;
    std::string contentLength_;
    std::string contentType_;
    std::string server_;
    std::string date_;
    std::string body_;
    int statusCode_;


public:
    Response(int responseType, const s_startline &startline, const s_headers &headers, const s_bodies &bodies);

const std::string &getResponse() const;

private:
    virtual void makeStartline();
    virtual void makeHeaders();
    virtual void makeBodies();

    void createResponse();

    void setAttributes();
    void setDate();
    void setContentLength();
    void setContentType();
    void setErrorBody();
    void doGetMethod();
    void doPostMethod();
    void doDeleteMethod();

    const std::string &getStatusLine() const;
    const std::string &getDate() const;
    const std::string &getBody() const;
    const std::string &getContentLength() const;
    
};

#endif
