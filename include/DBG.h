#include <Arduino.h>

#ifdef DEV_BUILD
#define DBG(x)                                                                 \
  do {                                                                         \
    Serial.println(x);                                                         \
  } while (0)
#else
#define DBG(x)                                                                 \
  do {                                                                         \
  } while (0)
#endif

#ifdef DEV_BUILD
#define DBGF(fmt, ...)                                                         \
  do {                                                                         \
    Serial.printf(fmt, ##__VA_ARGS__);                                         \
  } while (0)
#else
#define DBGF(fmt, ...)                                                         \
  do {                                                                         \
  } while (0)
#endif
