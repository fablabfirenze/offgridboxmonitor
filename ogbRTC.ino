
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

/*
 * RTC init
 */
void setupRTC()
{

  // Serial.print("Initializing RTC ...");
  #ifdef AVR
    Wire.begin();
  #else
    Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
  #endif
  rtc.begin();

  if (! rtc.isrunning()) {
    // Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  // Serial.println("RTC initialized.");
}
