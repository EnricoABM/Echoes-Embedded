#include "hardware/network/EspWifiStorage.hpp"
#include "DBG.h"

std::optional<WifiConnectDto> EspWifiStorage::restore() {
  auto ssid = prefs.getString("wifi-ssid");
  if (ssid == "")
    return std::nullopt;
  auto pass = prefs.getString("wifi-pass");
  auto ip = prefs.getString("wifi-ip");
  auto gateway = prefs.getString("wifi-gateway");
  auto subnet = prefs.getString("wifi-subnet");
  WifiConnectDto dto{ssid.c_str(), pass.c_str(), ip.c_str(), gateway.c_str(),
                     subnet.c_str()};
  DBG("[Wifi storage] restored");
  return dto;
}

void EspWifiStorage::save(WifiConnectDto dto) {
  DBG("[Wifi storage] saving...");
  prefs.putString("wifi-ssid", dto.ssid.c_str());
  prefs.putString("wifi-pass", dto.pass.c_str());
  prefs.putString("wifi-ip", dto.ip.c_str());
  prefs.putString("wifi-gateway", dto.gateway.c_str());
  prefs.putString("wifi-subnet", dto.subnet.c_str());
}
