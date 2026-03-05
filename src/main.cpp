#include <Arduino.h>
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

auto statusNetwork = std::make_shared<WifiNetworkDto>();
auto networks = std::make_shared<WifiNetworkList>();
Preferences prefs;
EspWifiAP wifiAP;
EspWifiScanner wifiScanner{networks, statusNetwork};
EspWifiStorage wifiStorage{prefs};
EspWifiSTA wifiSTA{statusNetwork};
EspWifiReconnector wifiReconnector{wifiStorage, wifiSTA};
WifiManager wifi{wifiAP, wifiScanner, wifiStorage, wifiSTA};

extern "C" void app_main(void) {
  initArduino();

  WiFi.mode(WIFI_AP_STA);
  WiFi.setSleep(false);

  wifiSTA.registerObserver(new APToggler(wifiAP));
  wifiSTA.registerObserver(new ReconnectorToggler(wifiReconnector));
  wifiSTA.registerObserver(new IndicatorToggler());
  wifiSTA.registerObserver(new MDNSToggler());

  while (true) {
    digitalWrite(2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(2, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
    Serial.println("Hello World!");
  }
}
