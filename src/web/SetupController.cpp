#include <Arduino.h>
#include <ArduinoJson.h>

#include "DBG.h"
#include "application/network/dto/WifiNetworkDto.hpp"
#include "web/SetupController.hpp"

void SetupController::setup() {
  server.on("/api/wifi", HTTP_GET, [this](AsyncWebServerRequest *request) {
    handleList(*this, request);
  });
  server.on(
      "/api/wifi/status", HTTP_GET,
      [this](AsyncWebServerRequest *request) { handleStatus(*this, request); });
  server.on(
      "/api/wifi/setup", HTTP_POST,
      [](AsyncWebServerRequest *request) {
        // do nothing here yet
      },
      nullptr,
      [this](AsyncWebServerRequest *request, uint8_t *data, size_t len,
             size_t index, size_t total) {
        handleSetup(*this, request, data, len, index, total);
      });
}

void SetupController::handleSetup(SetupController &setupController,
                                  AsyncWebServerRequest *request, uint8_t *data,
                                  size_t len, size_t index, size_t total) {

  static String body;
  if (index == 0)
    body = ""; // first chunk
  body += String((char *)data).substring(0, len);

  if (index + len != total)
    return;

  if (request->method() != HTTP_POST) {
    auto *badRes =
        request->beginResponse(405, "text/plain", "Method not allowed");
    request->send(badRes);
    return;
  }

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, body);
  if (err)
    return;

  String ssid = doc["ssid"];
  String pass = doc["pass"];
  String ip = doc["ip"];
  String gateway = doc["gateway"];
  String subnet = doc["subnet"];
  WifiConnectDto cmd{ssid.c_str(), pass.c_str(), ip.c_str(), gateway.c_str(),
                     subnet.c_str()};
  auto *res = request->beginResponse(200);
  res->addHeader("Cache-Control", "no-store");
  res->addHeader("Connection", "close");
  request->send(res);
  setupController.wifiStorage.save(cmd);
  setupController.wifiSTA.connect(cmd);
}

void SetupController::handleList(SetupController &setupController,
                                 AsyncWebServerRequest *request) {
  JsonDocument doc;
  JsonArray array = doc.to<JsonArray>();

  for (auto network : *setupController.networks) {
    JsonObject o = array.add<JsonObject>();
    o["ssid"] = network.ssid;
    o["secure"] = network.secure;
    o["status"] = static_cast<int>(network.status);
    o["rssi"] = network.rssi;
  }
  String json;
  serializeJson(doc, json);
  auto *res = request->beginResponse(200, "application/json", json);
  res->addHeader("Cache-Control", "no-store");
  res->addHeader("Connection", "close");
  request->send(res);
}

void SetupController::handleStatus(SetupController &setupController,
                                   AsyncWebServerRequest *request) {
  JsonDocument doc;
  doc["ssid"] = setupController.statusNetwork->ssid;
  doc["status"] = static_cast<int>(setupController.statusNetwork->status);
  doc["rssi"] = setupController.statusNetwork->rssi;
  String json;
  serializeJson(doc, json);
  auto *res = request->beginResponse(200, "application/json", json);
  res->addHeader("Cache-Control", "no-store");
  res->addHeader("Connection", "close");
  request->send(res);
}
