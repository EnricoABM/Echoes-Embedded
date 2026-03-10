#pragma once

#include "application/network/WifiSTA.hpp"
#include "application/network/WifiStorage.hpp"
#include "application/network/dto/WifiNetworkDto.hpp"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class SetupController {
public:
  SetupController(AsyncWebServer &server, WifiStorage &wifiStorage,
                  WifiSTA &wifiSTA, WifiNetworkPtr statusNetwork,
                  WifiNetworkListPtr networks)
      : server(server), wifiStorage(wifiStorage), wifiSTA(wifiSTA),
        statusNetwork(statusNetwork), networks(networks) {}
  void setup();

private:
  bool running{false};
  AsyncWebServer &server;

  WifiStorage &wifiStorage;
  WifiSTA &wifiSTA;
  WifiNetworkPtr statusNetwork;
  WifiNetworkListPtr networks;

  static void handleSetup(SetupController &setupServer,
                          AsyncWebServerRequest *request, uint8_t *data,
                          size_t len, size_t index, size_t total);
  static void handleList(SetupController &setupServer,
                         AsyncWebServerRequest *request);
  static void handleStatus(SetupController &setupServer,
                           AsyncWebServerRequest *request);
};
