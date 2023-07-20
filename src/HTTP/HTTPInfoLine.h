
#ifndef HTTP_INFO_LINE_h
#define HTTP_INFO_LINE_h

#include <Arduino.h>

class HTTPInfoLine {
public:
    String method;
    String uri;
    String http_version;

    HTTPInfoLine(
        String method,
        String uri,
        String http_version
    ) : method(method), uri(uri), http_version(http_version) {
    };

    operator String() const {
        const char* method_ = method.c_str();
        const char* uri_ = uri.c_str();
        const char* http_version_ = http_version.c_str(); // unparsed

        char* buf = (char*)calloc(strlen(method_) + strlen(uri_) + strlen(http_version_) + 3, sizeof(char));

        sprintf(buf, "%s %s %s",
            method.c_str(),
            uri.c_str(),
            http_version.c_str()
        );

        String out(buf);
        free(buf);
        return out;
    }
};


#endif
