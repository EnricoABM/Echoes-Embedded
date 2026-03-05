#pragma once

#include "application/network/dto/WifiConnectDto.hpp"
#include <optional>

class WifiStorage {
public:
  virtual ~WifiStorage() = default;

  virtual std::optional<WifiConnectDto> restore() = 0;
  virtual void save(WifiConnectDto dto) = 0;
};
