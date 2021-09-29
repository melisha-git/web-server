#include "Response.class.hpp"

//Response::Response(const s_startline &startline, const s_headers &headers, const s_bodies &bodies) {
//	this->s_startline_ = startline;
//	this->s_headers_ = headers;
//	this->s_bodies_ = bodies;
//	makeStartline();
//	makeHeaders();
//	makeBodies();
//}
//
void Response::makeStartline() {

}

void Response::makeHeaders() {

}

void Response::makeBodies() {

}

const std::string &Response::getResponse() const {
	return response_;
}

Response::Response(int responseType) : responseType_(responseType) {
    setAttributes();
    createResponse();
}

void Response::setAttributes() {
    setStatusLine();
    setDate();
//    if (responseType_ != 200)
    setErrorBody();
    setContentLength();
}

void Response::setDate() {
    const std::string day[]={"Sun","Mon","Tue",
                             "Wed","Thu","Fri","Sat"};

    const std::string month[]={"Jan","Feb","Mar",
                               "Apr","May","Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    time_t	rawTime;
    struct	tm * timeInfo;
    std::ostringstream out;

    time (&rawTime);
    timeInfo = localtime (&rawTime);

    out << day[timeInfo->tm_wday] << ", "
    << std::setw(2) << std::setfill('0') << timeInfo->tm_mday << " "
    << month[timeInfo->tm_mon] << " "
    << (timeInfo->tm_year + 1900) << " "
    << std::setw(2) << std::setfill('0') << timeInfo->tm_hour << ":"
    << std::setw(2) << std::setfill('0') << timeInfo->tm_min << ":"
    << std::setw(2) << std::setfill('0') << timeInfo->tm_sec << " GMT";
    date_ = out.str();
}

void Response::setStatusLine() {
    statusLine_ = "HTTP/1.1 ";

    std::string const arrStatus[] = {"200 OK", "400 Bad Request", "404 Not Found", "405 Method Not Allowed",
                                     "501 Not Implemented", "505 HTTP Version Not Supported"};
    std::ostringstream ss;
    ss << responseType_;

    std::string errorNumber = ss.str();

    for (int i = 0; i < 5 ; i++)
        if ((arrStatus[i].find(errorNumber)) != std::string::npos)
        {
            statusLine_.append(arrStatus[i]);
            break;
        }
}

void Response::setErrorBody() {
    switch (responseType_) {
        case 200:
            body_ = error_200;
            break;
        case 400:
            body_ = error_400;
            break;
        case 401:
            body_ = error_401;
            break;
        case 403:
            body_ = error_403;
            break;
        case 404:
            body_ = error_404;
            break;
        case 405:
            body_ = error_405;
            break;
        case 418:
            body_ = error_418;
            break;
        case 501:
            body_ = error_501;
            break;
        case 505:
            body_ = error_505;
            break;
    }
}

void Response::setContentLength() {
    std::ostringstream ss;

    ss << body_.length();
    contentLength_ = ss.str();
}

void Response::createResponse() {
    response_.append(getStatusLine() + "\r\n");
    response_.append("date: " + getDate() + "\r\n");
    response_.append("content-length: " + getContentLength() + "\r\n");

    if (responseType_ == 405)
        response_.append("allow: GET, POST, DELETE\r\n");

    response_.append(getBody());
}

std::string Response::getStatusLine() const { return statusLine_; }

std::string Response::getDate() const { return date_;}

std::string Response::getBody() const { return body_; }

std::string Response::getContentLength() const { return contentLength_; }

