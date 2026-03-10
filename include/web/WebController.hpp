#pragma once

#include <ESPAsyncWebServer.h>

class WebController {
public:
  WebController(AsyncWebServer &server) : server(server) {}
  void setup();

private:
  AsyncWebServer &server;

  static void handleFile(WebController &webController,
                         AsyncWebServerRequest *request);
  static String getContentType(String filename);
};
