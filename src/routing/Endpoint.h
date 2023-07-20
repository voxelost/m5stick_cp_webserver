
#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <Arduino.h>
#include "HTTP/HTTPUtils.h"
#include "HTTP/HTTPRequest.h"
#include "HTTP/HTTPResponse.h"

class Endpoint {
private:
    String(*func)(const HTTPRequest&);

public:
    Endpoint(String(*func)(const HTTPRequest&) = NULL) : func(func) {};
    size_t run(const HTTPRequest& request, WiFiClient& client) {
        HTTPResponse resp(build_response(func(request)));
        return send_response(resp, client);
    }
};

#endif
