#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#include "application/network/WifiSTA.hpp"

enum class WifiActionType { CONNECT, RECONNECT };

struct WifiAction {
  WifiActionType type;
  WifiConnectDto connectDto;
};

class WifiSTAProxy : public WifiSTA {
private:
  WifiSTA &base;
  QueueHandle_t queue;
  TaskHandle_t taskHandle;

  static void taskEntry(void *arg) {
    reinterpret_cast<WifiSTAProxy *>(arg)->taskLoop();
  }

  void taskLoop() {
    WifiAction action;

    while (true) {
      if (xQueueReceive(queue, &action, portMAX_DELAY)) {

        switch (action.type) {

        case WifiActionType::CONNECT:
          base.connect(action.connectDto);
          break;

        case WifiActionType::RECONNECT:
          base.reconnect();
          break;
        }
      }
    }
  }

public:
  WifiSTAProxy(WifiSTA &baseImpl) : base(baseImpl) {
    queue = xQueueCreate(10, sizeof(WifiAction));

    xTaskCreate(taskEntry, "wifi_proxy", 4096, this, 5, &taskHandle);
  }

  void connect(WifiConnectDto connectCmd) override {
    WifiAction action{WifiActionType::CONNECT, connectCmd};

    xQueueSend(queue, &action, portMAX_DELAY);
  }

  void reconnect() override {
    WifiAction action{WifiActionType::RECONNECT, {}};

    xQueueSend(queue, &action, portMAX_DELAY);
  }

  bool isConnected() override { return base.isConnected(); }

  void registerObserver(WifiObserver *observer) override {
    base.registerObserver(observer);
  }

  void unregisterObserver(WifiObserver *observer) override {
    base.unregisterObserver(observer);
  }

  ~WifiSTAProxy() {
    if (queue) {
      vQueueDelete(queue);
    }
  }
};
