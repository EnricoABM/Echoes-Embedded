#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <memory>

#include "application/APToggler.hpp"
#include "application/ReconnectorToggler.hpp"
#include "application/WifiManager.hpp"
#include "hardware/IndicatorToggler.hpp"
#include "hardware/MDNSToggler.hpp"
#include "hardware/network/EspWifiAP.hpp"
#include "hardware/network/EspWifiReconnector.hpp"
#include "hardware/network/EspWifiSTA.hpp"
#include "hardware/network/EspWifiScanner.hpp"
#include "hardware/network/EspWifiStorage.hpp"
#include "hardware/network/WifiSTAProxy.hpp"
#include "web/SetupController.hpp"
#include "web/WebController.hpp"

auto statusNetwork = std::make_shared<WifiNetworkDto>();
auto networks = std::make_shared<WifiNetworkList>();
Preferences prefs;
EspWifiAP wifiAP;
EspWifiScanner wifiScanner{networks, statusNetwork};
EspWifiStorage wifiStorage{prefs};
EspWifiSTA espWifiSTA{statusNetwork};
WifiSTAProxy wifiSTA{espWifiSTA};
EspWifiReconnector wifiReconnector{wifiStorage, wifiSTA};
WifiManager wifi{wifiAP, wifiScanner, wifiStorage, wifiSTA};

AsyncWebServer server{80};
SetupController setupController{server, wifiStorage, wifiSTA, statusNetwork,
                                networks};
WebController webController{server};

extern "C" void app_main(void) {
  initArduino();

  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);
  WiFi.setSleep(false);

  wifiSTA.registerObserver(new APToggler(wifiAP));
  wifiSTA.registerObserver(new ReconnectorToggler(wifiReconnector));
  wifiSTA.registerObserver(new IndicatorToggler());
  wifiSTA.registerObserver(new MDNSToggler());

  setupController.setup();
  webController.setup();

  server.begin();

  wifi.start();

  while (true) {
    wifiAP.loop();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
