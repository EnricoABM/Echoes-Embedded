#include "hardware/network/EspWifiReconnector.hpp"
#include "Config.h"
#include "DBG.h"

EspWifiReconnector::EspWifiReconnector(WifiStorage &wifiStorage,
                                       WifiSTA &wifiSTA)
    : wifiStorage(wifiStorage), wifiSTA(wifiSTA) {
  timer = xTimerCreate("WifiReconnector", pdMS_TO_TICKS(WIFI_RECONNECT_TIMER),
                       pdTRUE, this, EspWifiReconnector::reconnectTimer);
}

void EspWifiReconnector::start() { xTimerStart(timer, 0); }

void EspWifiReconnector::stop() { xTimerStop(timer, 0); }

void EspWifiReconnector::reconnectTimer(TimerHandle_t xTimer) {
  auto *reconnect =
      static_cast<EspWifiReconnector *>(pvTimerGetTimerID(xTimer));
  auto dto = reconnect->wifiStorage.restore();
  if (!dto)
    return;

  DBG("[WifiReconnector] Reconnecting to wifi");
  reconnect->wifiSTA.connect(*dto);
}
