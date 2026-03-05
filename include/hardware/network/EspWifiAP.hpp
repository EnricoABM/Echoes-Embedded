#pragma once

#include "application/network/WifiAP.hpp"
#include <DNSServer.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <vector>

class EspWifiAP : public WifiAP {
public:
  EspWifiAP();
  void start() override;
  void stop() override;
  void loop() override;
  uint16_t countConnected() override;
  void registerObserver(WifiObserver *observer) override;
  void unregisterObserver(WifiObserver *observer) override;

private:
  bool running{false};
  std::vector<WifiObserver *> observers;
  DNSServer dns;
  const byte DNS_PORT{53};
  uint16_t countConnect;

  IPAddress apIP{192, 168, 4, 1};
  IPAddress gateway{192, 168, 4, 1};
  IPAddress subnet{255, 255, 255, 0};

  static EspWifiAP *instance;
  static void onWifiEvent(WiFiEvent_t event);
};
