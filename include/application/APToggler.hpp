#pragma once

#include "network/WifiAP.hpp"
#include "network/WifiObserver.hpp"

class APToggler : public WifiObserver {
public:
  APToggler(WifiAP &wifiAP);
  void onConnect() override;
  void onDisconnect() override;

private:
  WifiAP &wifiAP;
};
