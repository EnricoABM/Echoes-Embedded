#pragma once

#include <memory>
#include <vector>

enum class WifiStatus {
  WIFI_NONE = 0,
  WIFI_CONNECTING,
  WIFI_CONNECTED,
  WIFI_ERROR
};

struct WifiNetworkDto {
  std::string ssid;
  bool secure;       // true = needs password
  WifiStatus status; // 0..3
  int32_t rssi;
};

using WifiNetworkPtr = std::shared_ptr<WifiNetworkDto>;
using WifiNetworkList = std::vector<WifiNetworkDto>;
using WifiNetworkListPtr = std::shared_ptr<WifiNetworkList>;
