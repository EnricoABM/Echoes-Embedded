#pragma once

#include "network/WifiObserver.hpp"
#include "network/WifiReconnector.hpp"

class ReconnectorToggler : public WifiObserver {
public:
  ReconnectorToggler(WifiReconnector &wifiReconnector)
      : wifiReconnector(wifiReconnector) {};
  void onConnect() override;
  void onDisconnect() override;

private:
  WifiReconnector &wifiReconnector;
};
