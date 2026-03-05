#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

#include "application/network/WifiReconnector.hpp"
#include "application/network/WifiSTA.hpp"
#include "application/network/WifiStorage.hpp"

class EspWifiReconnector : public WifiReconnector {
public:
  EspWifiReconnector(WifiStorage &wifiStorage, WifiSTA &wifiSTA);
  void start() override;
  void stop() override;

private:
  WifiStorage &wifiStorage;
  WifiSTA &wifiSTA;
  TimerHandle_t timer;

  static void reconnectTimer(TimerHandle_t xTimer);
};
