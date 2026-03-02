#include <Arduino.h>

extern "C" void app_main(void) {
  initArduino();

  pinMode(2, OUTPUT);
  Serial.begin(115200);

  while (true) {
    digitalWrite(2, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(2, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
    Serial.println("Hello World!");
  }
}
