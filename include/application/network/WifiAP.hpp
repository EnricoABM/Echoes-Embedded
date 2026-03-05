#pragma once

#include "application/network/WifiObserver.hpp"
#include <cstdint>

class WifiAP {
public:
  virtual ~WifiAP() = default;

  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void loop() = 0;
  virtual uint16_t countConnected() = 0;
  virtual void registerObserver(WifiObserver *observer) = 0;
  virtual void unregisterObserver(WifiObserver *observer) = 0;
};
