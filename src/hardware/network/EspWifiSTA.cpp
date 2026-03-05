#include "hardware/network/EspWifiSTA.hpp"
#include "Config.h"
#include "DBG.h"

EspWifiSTA *EspWifiSTA::instance = nullptr;

EspWifiSTA::EspWifiSTA(WifiNetworkPtr statusNetwork)
    : statusNetwork(statusNetwork) {
  EspWifiSTA::instance = this;
  WiFi.onEvent(EspWifiSTA::onWiFiEvent);
}

void EspWifiSTA::reconnect() { WiFi.reconnect(); }

void EspWifiSTA::connect(WifiConnectDto connectCmd) {
  statusNetwork->ssid = connectCmd.ssid;
  statusNetwork->status = WifiStatus::WIFI_CONNECTING;
  if (connectCmd.isDHCP())
    connectDHCP(connectCmd);
  else
    connectStatic(connectCmd);
}

void EspWifiSTA::connectDHCP(WifiConnectDto connectCmd) {
  DBG("Connecting to WiFi [DHCP]:");
  DBG(connectCmd.ssid);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
  connect(connectCmd.ssid, connectCmd.pass);
}

void EspWifiSTA::connectStatic(WifiConnectDto connectCmd) {
  DBG("Connecting to WiFi [Static]:");
  DBG(connectCmd.ssid);
  DBG("IP: " + connectCmd.ip);
  DBG("Gateway: " + connectCmd.gateway);
  DBG("Subnet: " + connectCmd.subnet);

  IPAddress ipParsed, gatewayParsed, subnetParsed;
  IPAddress dns1(8, 8, 8, 8);
  IPAddress dns2(8, 8, 4, 4);

  auto failParseIps = !ipParsed.fromString(connectCmd.ip.c_str()) ||
                      !gatewayParsed.fromString(connectCmd.gateway.c_str()) ||
                      !subnetParsed.fromString(connectCmd.subnet.c_str());
  if (failParseIps) {
    statusNetwork->status = WifiStatus::WIFI_ERROR;
    return;
  }

  WiFi.config(ipParsed, gatewayParsed, subnetParsed, dns1, dns2);
  connect(connectCmd.ssid, connectCmd.pass);
}

void EspWifiSTA::connect(std::string ssid, std::string pass) {
  if (isConnected())
    WiFi.disconnect();

  WiFi.setAutoReconnect(false);
  WiFi.persistent(false);
  WiFi.begin(ssid.c_str(), pass.c_str());
  int tries = 0;
  while (!isConnected() && tries < 25) {
    vTaskDelay(pdMS_TO_TICKS(200));
    tries++;
  }
  if (isConnected())
    vTaskDelay(pdMS_TO_TICKS(200));
  else
    statusNetwork->status = WifiStatus::WIFI_ERROR;
}

bool EspWifiSTA::isConnected() {
  return WiFi.status() == WL_CONNECTED && WiFi.localIP() != INADDR_NONE;
}

void EspWifiSTA::registerObserver(WifiObserver *observer) {
  observers.push_back(observer);
}

void EspWifiSTA::unregisterObserver(WifiObserver *observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer),
                  observers.end());
}

void EspWifiSTA::onWiFiEvent(WiFiEvent_t event) {
  if (!instance)
    return;

  if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP) {
    instance->statusNetwork->status = WifiStatus::WIFI_CONNECTED;
    DBG("[Wifi] Connected and Got IP");
    DBG(WiFi.localIP());
    for (auto obs : instance->observers) {
      obs->onConnect();
    }
  }
  if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
    DBG("[Wifi] Disconnect from Wifi");
    if (instance->statusNetwork->status == WifiStatus::WIFI_CONNECTED)
      instance->statusNetwork->status = WifiStatus::WIFI_NONE;

    for (auto obs : instance->observers) {
      obs->onDisconnect();
    }
  }
}
