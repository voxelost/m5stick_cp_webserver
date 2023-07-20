#include <WiFi.h>
#include "M5StickCPlus.h"
#include "HTTP/HTTPServer.h"
// #include "HTTP/HTTPUtils.h"
#include "endpoints.h"

#include "wifi_credentials.h" // comment this out if you dont want to add a credentials file
#ifndef wifi_credentials_
#define wifi_credentials_
#define WIFI_SSID ("")
#define WIFI_PASSWORD ("")
#endif


WiFiServer wifi_server(80);
HTTPServer http_server;

void setup() {
  m5.begin(true, true, true, 9600UL);

  printf_d("connecting to %s\n", WIFI_SSID);

  for (int trial = 0; !WiFi.isConnected(); trial++) {
    if (!(trial % 10)) {
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }

    delay(500);
    printf_d(".");
  }

  wifi_server.begin();
  printf_d("\nconnected to wifi (%s)\n", WiFi.localIP().toString().c_str());


  const std::vector<std::pair<const char*, String(*)(const HTTPRequest& request)>> endpoints = {
    {"/echo", echo},
    {"/gyro", gyro_data},
    {"/temp", temp},
    {"/json", json},
  };

  for (auto endpoint : endpoints) {
    http_server.register_endpoint(endpoint.first, endpoint.second);
  }
}


void loop() {
  http_server.set_client(wifi_server.available());
  http_server.listen();
}
