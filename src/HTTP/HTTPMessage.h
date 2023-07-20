#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#include <vector>
#include <WiFi.h>
#include "HTTPHeader.h"
#include "HTTPBody.h"


class HTTPMessage {
public:
    std::vector<HTTPHeader> headers;
    HTTPBody body;

    HTTPMessage(std::vector<HTTPHeader> headers, String body) : headers(headers), body(body) {};

    operator String () const {
        int buf_size = strlen(String(body).c_str()) + 3; // + \r\n + \0

        for (HTTPHeader header : headers) {
            buf_size += strlen(header.key.c_str()) + strlen(header.value.c_str()) + 4; // + ": " + \r\n
        }

        char* buf = (char*)calloc(buf_size, sizeof(char));

        int offset = 0;
        for (HTTPHeader header : headers) {
            sprintf(buf + offset, "%s\r\n", String(header).c_str());
            offset += strlen(header.key.c_str()) + strlen(header.value.c_str()) + 4;
        }

        sprintf(buf + offset, "\r\n");
        offset += 2;

        sprintf(buf + offset, String(body).c_str()); // creating a temporary variable here causes an error

        String out(buf);
        free(buf);

        return out;
    }
};


#endif
