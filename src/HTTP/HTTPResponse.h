
#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <vector>
#include <Arduino.h>
#include "HTTPMessage.h"
#include "HTTPStatusLine.h"

class HTTPResponse : public HTTPMessage {
public:
    HTTPStatusLine status_line;

    HTTPResponse(HTTPStatusLine status_line, std::vector<HTTPHeader> headers, HTTPBody body) : status_line(status_line), HTTPMessage(headers, body) {};

    operator String() const {
        const char* rest = HTTPMessage::operator String().c_str();
        char* buf = (char*)calloc(strlen(String(status_line).c_str()) + strlen(rest) + 3, sizeof(char));

        sprintf(buf, "%s\r\n%s", String(status_line).c_str(), rest);
        String out(buf);
        free(buf);
        return out;
    }
};

#endif
