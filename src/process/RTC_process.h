#ifndef _RTC_H_
#define _RTC_H_
#include <Arduino.h>
void RTC_SETUP();
void RTC_PROGRAM();
byte RTC_GET_HOUR();
byte RTC_GET_MINUTE();
byte RTC_GET_SECOND();
byte RTC_GET_DATE();
byte RTC_GET_MONTH();
uint16_t RTC_GET_YEAR();
bool RTC_GET_FLAG();
#endif