#pragma once

#include "application/network/WifiScanner.hpp"
#include "application/network/dto/WifiNetworkDto.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class EspWifiScanner : public WifiScanner {
public:
  EspWifiScanner(WifiNetworkListPtr networks, WifiNetworkPtr statusNetwork);
  void start();
  void stop();

private:
  bool running{false};
  WifiNetworkPtr statusNetwork;
  TaskHandle_t scanTaskHandle;
  static void scanTask(void *param);
  void processScan();
  WifiNetworkDto processScanItem(int i);
};
