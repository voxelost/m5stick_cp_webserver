
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <Arduino.h>
#include <map>
#include <vector>

#include "WiFiClient.h"
#include "HTTPInfoLine.h"
#include "HTTPHeader.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "M5StickCPlus.h"
#include "HTTPUtils.h"
#include "routing/EndpointRouter.h"


class HTTPServer {
private:
    WiFiClient _wifi_client;
    EndpointRouter _endpoint_router;

    HTTPInfoLine parse_request_info_line(String& raw_line) {
        int first_space_idx = raw_line.indexOf(' ');
        int second_space_idx = raw_line.indexOf(' ', first_space_idx + 1);

        return HTTPInfoLine(
            String(raw_line.c_str(), first_space_idx),
            String(raw_line.c_str() + first_space_idx + 1, second_space_idx - first_space_idx - 1),
            String(raw_line.c_str() + second_space_idx + 1, strlen(raw_line.c_str()) - second_space_idx)
        );
    }

    std::vector<HTTPHeader> parse_request_headers(std::vector<String>& raw_lines) {
        std::vector<HTTPHeader> out;

        for (String& raw_line : raw_lines) {
            int sep_idx = raw_line.indexOf(':');
            const char* raw_line_ = raw_line.c_str();

            out.push_back(HTTPHeader(
                String(raw_line_, sep_idx),
                String(raw_line_ + sep_idx + 2)
            ));
        }

        return out;
    }

    String read_until(char delimiter = 0xff, bool end_on_newline = true) {
        String line;
        while (_wifi_client.connected() && _wifi_client.available()) {
            char c = _wifi_client.read();
            if (c == delimiter || (end_on_newline && c == '\n')) {
                break;
            }

            if (c != '\r') {
                line.concat(c);
            }
        }

        return line;
    }

    String read_line() {
        return read_until(0xff, true);
    }

    HTTPRequest build_request() {
        String line = read_line();
        HTTPInfoLine info_line = parse_request_info_line(line);
        std::vector<String> header_lines;
        for (;;) {
            String line = read_line();

            if (line.length() < 1) {
                break;
            }
            header_lines.push_back(line);
        }

        return HTTPRequest(
            info_line,
            parse_request_headers(header_lines),
            HTTPBody(read_until(0xff, false))
        );
    }

    size_t try_endpoint(HTTPRequest& request) {
        return _endpoint_router.try_path(request.info_line.uri, request, _wifi_client);
    }

public:
    HTTPServer() : _wifi_client(), _endpoint_router() {};
    HTTPServer(WiFiClient wifi_client) : _wifi_client(wifi_client), _endpoint_router() {};
    void set_client(const WiFiClient& wifi_client) {
        _wifi_client = wifi_client;
    }

    size_t listen() {
        if (_wifi_client.available()) {
            HTTPRequest request = build_request();
            try_endpoint(request);
            // printf_d("written %d bytes\n", written);
        }

        return 0;
    }

    void register_endpoint(const String& path, const Endpoint& endpoint) {
        return _endpoint_router.register_endpoint(path, endpoint);
    }




    ~HTTPServer() {
        _wifi_client.stop();
    }
};


#endif
