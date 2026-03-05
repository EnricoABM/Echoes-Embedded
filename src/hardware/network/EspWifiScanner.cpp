#include "hardware/network/EspWifiScanner.hpp"
#include "Config.h"
#include "DBG.h"
#include <WiFi.h>

EspWifiScanner::EspWifiScanner(WifiNetworkListPtr networks,
                               WifiNetworkPtr statusNetwork)
    : WifiScanner(networks), statusNetwork(statusNetwork) {
  xTaskCreate(EspWifiScanner::scanTask, "wifi-scan", 4096, this, 1,
              &scanTaskHandle);
}

void EspWifiScanner::start() {
  if (running)
    return;

  DBG("[Wifi Scanner] Starting...");
  vTaskResume(scanTaskHandle);
  WiFi.scanNetworks(true, true);
  running = true;
}

void EspWifiScanner::stop() {
  if (!running)
    return;

  DBG("[Wifi Scanner] Stopping...");
  vTaskSuspend(scanTaskHandle);
  WiFi.scanDelete();
  running = false;
}

void EspWifiScanner::scanTask(void *param) {
  auto *self = static_cast<EspWifiScanner *>(param);
  while (true) {
    vTaskDelay(pdMS_TO_TICKS(WIFI_SCAN_TASK_DELAY));
    self->processScan();
    WiFi.scanNetworks(true, true);
  }
}

void EspWifiScanner::processScan() {
  int n = WiFi.scanComplete();

  if (n <= 0)
    return;
  WifiNetworkList newNetworks;

  for (int i = 0; i < n; i++) {
    auto net = processScanItem(i);
    newNetworks.push_back(net);
  }

  networks->swap(newNetworks);
  WiFi.scanDelete();
}

WifiNetworkDto EspWifiScanner::processScanItem(int i) {
  WifiNetworkDto net;
  net.ssid = WiFi.SSID(i).c_str();
  net.secure = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
  net.status = WifiStatus::WIFI_NONE;
  net.rssi = WiFi.RSSI(i);
  if (net.ssid == statusNetwork->ssid)
    net.status = statusNetwork->status;
  return net;
}
