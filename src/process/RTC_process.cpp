#include "process/RTC_process.h"
#include <RTClib.h>
static boolean RTC_FLAG = 0;
RTC_DS3231 rtc;
DateTime now;
static uint32_t RTC_WAIT_TIME;
static byte old_second;

void RTC_SETUP()
{
    if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1)
      delay(10);
  }
  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
void RTC_PROGRAM()
{
if(millis() - RTC_WAIT_TIME > 200)
{
RTC_WAIT_TIME = millis();
now = rtc.now();
if (now.second() != old_second)
    {
      old_second = now.second();
      {
        RTC_FLAG = 1;  
    
      }
    }
}
}
bool RTC_GET_FLAG()
{
  return RTC_FLAG;
}
byte RTC_GET_HOUR()
{
  return now.hour();
}
byte RTC_GET_MINUTE()
{
  return now.minute();
}
byte RTC_GET_SECOND()
{
  return now.second();
}
byte RTC_GET_DATE()
{
  return now.dayOfTheWeek();
}
byte RTC_GET_MONTH()
{
  return now.month();
}
uint16_t RTC_GET_YEAR()
{
  return now.year();
}