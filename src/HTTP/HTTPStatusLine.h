#ifndef HTTP_STATUS_LINE_H
#define HTTP_STATUS_LINE_H

#include <Arduino.h>

class HTTPStatusLine {
public:
    String version;
    int code;
    String reason_phrase;

    HTTPStatusLine(
        String version, // unparsed
        int code,
        String reason_phrase
    ) : version(version), code(code), reason_phrase(reason_phrase) {
    };

    operator String() const {
        char* buf = (char*)calloc(strlen(version.c_str()) + strlen(reason_phrase.c_str()) + 13, sizeof(char));
        sprintf(buf, "%s %d %s",
            version.c_str(),
            code,
            reason_phrase.c_str()
        );

        String out(buf);
        free(buf);
        return out;
    }
};


#endif
