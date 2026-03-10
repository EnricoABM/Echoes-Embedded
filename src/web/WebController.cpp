#include <SPIFFS.h>

#include "web/WebController.hpp"

void WebController::setup() {
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS mount failed");
    return;
  }
  server.onNotFound(
      [this](AsyncWebServerRequest *request) { handleFile(*this, request); });
}

void WebController::handleFile(WebController &webController,
                               AsyncWebServerRequest *request) {
  String path = request->url();
  if (path.endsWith("/"))
    path += "index.html";
  if (!SPIFFS.exists(path))
    path = "/index.html";

  auto contentType = getContentType(path);

  auto *res = request->beginResponse(SPIFFS, path, contentType);
  res->addHeader("Cache-Control", "no-store");
  res->addHeader("Connection", "close");
  request->send(res);
}

String WebController::getContentType(String filename) {
  if (filename.endsWith(".html"))
    return "text/html";
  if (filename.endsWith(".css"))
    return "text/css";
  if (filename.endsWith(".js"))
    return "application/javascript";
  if (filename.endsWith(".png"))
    return "image/png";
  if (filename.endsWith(".jpg"))
    return "image/jpeg";
  if (filename.endsWith(".svg"))
    return "image/svg+xml";
  if (filename.endsWith(".ico"))
    return "image/x-icon";
  return "text/plain";
}
