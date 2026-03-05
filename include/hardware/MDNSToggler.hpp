#pragma once

#include "application/network/WifiObserver.hpp"

class MDNSToggler : public WifiObserver {
public:
  void onConnect() override;
  void onDisconnect() override;
};
