
#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include <Arduino.h>
#include <vector>
#include "M5StickCPlus.h"
#include "HTTPStatusLine.h"
#include "HTTPHeader.h"
#include "HTTPResponse.h"
#include "WiFiClient.h"

template<typename... Args> void printf_d(const char* f, Args... args) {
    try {
        Serial.printf(f, args...);
        m5.Lcd.printf(f, args...);
    }
    catch (...) {
        return;
    }
}

HTTPResponse build_response(String response_body, std::vector<HTTPHeader> headers = {}) {
    return HTTPResponse(
        HTTPStatusLine(String("HTTP/1.1"), 200, String("OK")), // todo: add response code logic
        headers,
        response_body
    );
}

size_t send_response(HTTPResponse& response, WiFiClient& client) {
    size_t out = 0;
    out += client.printf("%s\r\n", String(response.status_line).c_str());

    for (HTTPHeader& header : response.headers) {
        out += client.printf("%s\r\n", String(header).c_str());
    }

    out += client.write("\r\n");
    out += client.write(String(response.body).c_str());
    return out;
}

#endif
