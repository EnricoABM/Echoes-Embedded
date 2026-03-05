#pragma once

#include "application/network/WifiSTA.hpp"
#include "application/network/dto/WifiConnectDto.hpp"
#include "application/network/dto/WifiNetworkDto.hpp"
#include <WiFi.h>

class EspWifiSTA : public WifiSTA {
public:
  EspWifiSTA(WifiNetworkPtr statusNetwork);
  void connect(WifiConnectDto connectCmd) override;
  void reconnect() override;
  bool isConnected() override;
  void registerObserver(WifiObserver *observer) override;
  void unregisterObserver(WifiObserver *observer) override;

private:
  std::vector<WifiObserver *> observers;
  WifiNetworkPtr statusNetwork;
  static EspWifiSTA *instance;

  void connectDHCP(WifiConnectDto connectCmd);
  void connectStatic(WifiConnectDto connectCmd);
  void connect(std::string ssid, std::string pass);
  static void onWiFiEvent(WiFiEvent_t event);
};
