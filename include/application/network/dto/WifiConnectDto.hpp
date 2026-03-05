#pragma once

#include <string>

struct WifiConnectDto {
  const std::string ssid;
  const std::string pass;
  const std::string ip;
  const std::string gateway;
  const std::string subnet;

  bool isDHCP() const { return ip == ""; }
};
