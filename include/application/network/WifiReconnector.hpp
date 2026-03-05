#pragma once

class WifiReconnector {
public:
  virtual ~WifiReconnector() = default;

  virtual void start() = 0;
  virtual void stop() = 0;
};
