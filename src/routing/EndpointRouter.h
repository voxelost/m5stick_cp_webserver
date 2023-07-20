

#ifndef ENDPOINT_ROUTER_H
#define ENDPOINT_ROUTER_H

#include <map>
#include <Arduino.h>

#include "Endpoint.h"
#include "WiFiClient.h"


class EndpointRouter {
private:
    std::map<String, Endpoint> _router;


public:
    EndpointRouter(std::map<String, Endpoint> router = {}) : _router(router) {};

    void register_endpoint(String path, Endpoint endpoint) {
        _router.insert({ path, endpoint });
    }

    size_t try_path(const String& path, HTTPRequest& request, WiFiClient& client) {
        if (_router.count(path) < 1) {
            HTTPResponse resp(
                HTTPStatusLine(String("HTTP/1.1"), 404, "not found"),
                {},
                HTTPBody(String("not found"))
            );
            return send_response(resp, client);
        }

        return _router[path].run(request, client);
    }
};

#endif
