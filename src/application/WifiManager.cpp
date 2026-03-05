#include "application/WifiManager.hpp"

#include "application/WifiManager.hpp"

void WifiManager::start() {
  auto dto = storage.restore();
  ap.start();
  scanner.start();

  if (dto)
    sta.connect(*dto);
}

void WifiManager::stop() {
  ap.stop();
  scanner.stop();
}
