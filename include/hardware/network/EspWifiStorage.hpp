#pragma once

#include "application/network/WifiStorage.hpp"
#include "application/network/dto/WifiConnectDto.hpp"

#include <Preferences.h>

class EspWifiStorage : public WifiStorage {
public:
  EspWifiStorage(Preferences &prefs) : prefs(prefs) {};
  std::optional<WifiConnectDto> restore() override;
  void save(WifiConnectDto dto) override;

private:
  Preferences &prefs;
};
