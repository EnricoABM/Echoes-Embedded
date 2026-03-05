#pragma once

#include "application/network/WifiObserver.hpp"

class IndicatorToggler : public WifiObserver {
public:
  IndicatorToggler();
  void onConnect() override;
  void onDisconnect() override;
};
