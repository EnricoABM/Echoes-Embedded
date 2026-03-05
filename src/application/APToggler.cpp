#include "application/APToggler.hpp"

APToggler::APToggler(WifiAP &wifiAP) : wifiAP(wifiAP) {}

void APToggler::onConnect() { wifiAP.stop(); }

void APToggler::onDisconnect() { wifiAP.start(); }
