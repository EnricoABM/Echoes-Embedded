#include "hardware/IndicatorToggler.hpp"
#include "Config.h"
#include <Arduino.h>

IndicatorToggler::IndicatorToggler() {
  pinMode(INDICATOR_PIN, OUTPUT);
  digitalWrite(INDICATOR_PIN, LOW);
}

void IndicatorToggler::onConnect() { digitalWrite(INDICATOR_PIN, HIGH); }

void IndicatorToggler::onDisconnect() { digitalWrite(INDICATOR_PIN, LOW); }
