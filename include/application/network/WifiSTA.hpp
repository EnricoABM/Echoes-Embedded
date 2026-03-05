#pragma once

#include "application/network/WifiObserver.hpp"
#include "application/network/dto/WifiConnectDto.hpp"

class WifiSTA {
public:
  virtual void connect(WifiConnectDto connectCmd) = 0;
  virtual void reconnect() = 0;
  virtual bool isConnected() = 0;
  virtual void registerObserver(WifiObserver *observer) = 0;
  virtual void unregisterObserver(WifiObserver *observer) = 0;

  virtual ~WifiSTA() = default;
};
