#pragma once

#include "application/network/dto/WifiNetworkDto.hpp"

class WifiScanner {
public:
  WifiScanner(WifiNetworkListPtr networks) : networks(networks) {};
  virtual void start() = 0;
  virtual void stop() = 0;

  virtual ~WifiScanner() = default;

protected:
  WifiNetworkListPtr networks;
};
