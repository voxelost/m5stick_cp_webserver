
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <vector>
#include "HTTPInfoLine.h"
#include "HTTPMessage.h"

class HTTPRequest : public HTTPMessage {
public:
    HTTPInfoLine info_line;

    HTTPRequest(HTTPInfoLine info_line, std::vector<HTTPHeader> headers, HTTPBody body) : info_line(info_line), HTTPMessage(headers, body) {};

    operator String() const {
        const char* rest = HTTPMessage::operator String().c_str();

        char* buf = (char*)calloc(strlen(String(info_line).c_str()) + strlen(rest) + 3, sizeof(char));

        sprintf(buf, "%s\r\n%s", String(info_line).c_str(), rest);
        String out(buf);
        free(buf);
        return out;
    }
};

#endif
