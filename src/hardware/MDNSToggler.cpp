#include "hardware/MDNSToggler.hpp"
#include <ESPmDNS.h>

void MDNSToggler::onConnect() {
  if (!MDNS.begin("echoes"))
    Serial.println("mDNS failed to start");
  else
    MDNS.addService("http", "tcp", 80);
}

void MDNSToggler::onDisconnect() { MDNS.end(); }
