#include "hardware/network/EspWifiAP.hpp"
#include "Config.h"
#include "DBG.h"

EspWifiAP *EspWifiAP::instance = nullptr;

EspWifiAP::EspWifiAP() {
  EspWifiAP::instance = this;
  WiFi.onEvent(EspWifiAP::onWifiEvent);
}

void EspWifiAP::start() {
  if (running)
    return;

  DBG("[WifiAP] Starting...");
  WiFi.softAPConfig(apIP, gateway, subnet);
  WiFi.softAP("Echoes Setup", nullptr, 0);
  dns.start(DNS_PORT, "*", apIP);

  running = true;
}

void EspWifiAP::stop() {
  if (!running)
    return;

  DBG("[WifiAP] Stopping...");
  WiFi.softAPdisconnect(true);
  dns.stop();

  running = false;
}

void EspWifiAP::loop() {
  if (!running)
    return;

  dns.processNextRequest();
}

uint16_t EspWifiAP::countConnected() { return countConnect; }

void EspWifiAP::registerObserver(WifiObserver *observer) {
  observers.push_back(observer);
}

void EspWifiAP::unregisterObserver(WifiObserver *observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer),
                  observers.end());
}

void EspWifiAP::onWifiEvent(WiFiEvent_t event) {
  switch (event) {
  case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
    instance->countConnect++;
    DBG("[WifiAP] Connected");
    for (auto obs : instance->observers)
      obs->onConnect();
    break;

  case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
    instance->countConnect--;
    DBG("[WifiAP] Disconnected");
    for (auto obs : instance->observers)
      obs->onDisconnect();
    break;

  default:
    break;
  }
}
