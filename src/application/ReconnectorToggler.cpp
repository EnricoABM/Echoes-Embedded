#include "application/ReconnectorToggler.hpp"

void ReconnectorToggler::onConnect() { wifiReconnector.start(); }

void ReconnectorToggler::onDisconnect() { wifiReconnector.stop(); }
