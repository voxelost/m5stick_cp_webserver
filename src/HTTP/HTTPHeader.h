
#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <Arduino.h>

class HTTPHeader {
public:
    String key;
    String value;

    HTTPHeader(String key, String value) : key(key), value(value) {};
    operator String() const {
        char* buf = (char*)calloc(strlen(key.c_str()) + strlen(value.c_str()) + 3, sizeof(char));
        sprintf(buf, "%s: %s", key.c_str(), value.c_str());
        String out(buf);
        free(buf);
        return out;
    }
};

#endif
