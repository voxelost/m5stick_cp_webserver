
#ifndef HTTP_BODY_H
#define HTTP_BODY_H

#include <Arduino.h>

class HTTPBody {
public:
    String body;
    HTTPBody(String body) : body(body) {};

    operator String() const {
        return body;
    }
};

#endif
