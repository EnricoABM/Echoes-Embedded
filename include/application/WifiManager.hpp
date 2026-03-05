#pragma once

#include "network/WifiAP.hpp"
#include "network/WifiSTA.hpp"
#include "network/WifiScanner.hpp"
#include "network/WifiStorage.hpp"

class WifiManager {
public:
  WifiManager(WifiAP &ap, WifiScanner &scanner, WifiStorage &storage,
              WifiSTA &sta)
      : ap(ap), scanner(scanner), storage(storage), sta(sta) {}
  void start();
  void stop();

private:
  WifiAP &ap;
  WifiScanner &scanner;
  WifiStorage &storage;
  WifiSTA &sta;
};
