#pragma once

class WifiObserver {
public:
  virtual void onConnect() = 0;
  virtual void onDisconnect() = 0;
};
