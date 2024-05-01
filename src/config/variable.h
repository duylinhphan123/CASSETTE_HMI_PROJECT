#define USE_IR 1
#define RTC_ENABLE 1
#define TIMER_CONTROL_ENABLE 1
#define DEBUG_PRG 1
#ifndef DEBUG_PRG

#define COVERT_NUMBER 1
#define FFT_ENABLE 1
#define SERIAL_DATA 1

#define SILENCE_FINDER_ENABLE 1
#define SERIAL_CODE_ENABLE 1

#define DIRECTION_CALCULATE 1
#define USE_EEPROM 1
#define BUTTON_CONTROL 1
#define TOTAL_PROGRAM 1
#define SERVO_CONTROL 1
#define AS5600_ENABLE 0
#define ENCODER_SIMULATION 1 
#define AUTO_PLAYBACK 1
#endif // DEBUG

#define VARIABLE_TAG 1

#if FFT_ENABLE
#include "fix_fft.h"
#endif

#define PREVIOUS_BUTTON 0
#define PLAY_BUTTON 1
#define PAUSE_BUTTON 2
#define STOP_BUTTON 3
#define NEXT_BUTTON 4
#define EJECT_BUTTON 5

#define PLAY_MODE 0
#define PREVIOUS_MODE 1
#define PAUSE_MODE 2
#define STOP_MODE 3
#define NEXT_MODE 4
#define EJECT_MODE 5
#define PRE_REC_MODE 6
#define PLAY_REC_MODE 7
#define NEXT_REC_MODE 8

#define SEND_HOUR 0
#define SEND_MINUTE 1
#define SEND_SECOND 2

#define CUE_MARK 0
#define CUE_HOUR 1
#define CUE_MINUTE 2
#define CUE_SECOND 3

#define TOTAL_MARK 3
#define TORAL_HOUR 0
#define TOTAL_MINUTE 1
#define TOTAL_SECOND 2

#define SIMU_REV 0
#define SIMU_PLAY 1
#define SIMU_STOP 2
#define SIMU_FOR 3

#define KEY_TRACK "TR"  
#define KEY_ENCODER "EN"
#define KEY_CLOCK "CL"
#define KEY_BUTTON "BT"
#define KEY_COMMAND "CM"
#define KEY_CUEPOINT "CE"
#define KEY_EQ "EQ"
#define KEY_TONE "TN"
#define KEY_TOTAL "TT"
#define KEY_MODE "MD"
#define KEY_REVOLUTION "RE"
#define KEY_RESET "RS"
#define KEY_REPLAY "RP"
#define KEY_RESETCUE "RC"
#define KEY_MOTOR "MT"
#define KEY_PLAYSET "PS"
#define KEY_PLAYMODE "PM"
#define PREVIOUS_CODE 0x46
#define PLAY_CODE 0x43
#define PAUSE_CODE 0x40
#define STOP_CODE 0x9
#define NEXT_CODE 0x1B
#define EJECT_CODE 0x30

#define MIN_TONE 0
#define MAX_TONE 1

#define CUE_ADDR  32
#define TOTAL_ADDR  4

#define IR_OVERFLOW_FLAG IRDATA_FLAGS_WAS_OVERFLOW

// //RESET DATE TIME CODE
// // #include <Arduino.h>
// // #include <SPI.h>

// // // Date and time functions using a DS3231 RTC connected via I2C and Wire lib
// // #include "RTClib.h"

// // RTC_DS3231 rtc;

// // char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// // void setup () {
// //   Serial.begin(57600);

// // #ifndef ESP8266
// //   while (!Serial); // wait for serial port to connect. Needed for native USB
// // #endif

// //   if (! rtc.begin()) {
// //     //Serial.println("Couldn't find RTC");
// //     Serial.flush();
// //     while (1) delay(10);
// //   }

// //   if (rtc.lostPower()) {
// //     //Serial.println("RTC lost power, let's set the time!");
// //     // When time needs to be set on a new device, or after a power loss, the
// //     // following line sets the RTC to the date & time this sketch was compiled
// //    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
// //     // This line sets the RTC with an explicit date & time, for example to set
// //     // January 21, 2014 at 3am you would call:
// //     // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
// //   }

// //   // When time needs to be re-set on a previously configured device, the
// //   // following line sets the RTC to the date & time this sketch was compiled
// //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
// //   // This line sets the RTC with an explicit date & time, for example to set
// //   // January 21, 2014 at 3am you would call:
// //   // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
// // }

// // void loop () {
// //     DateTime now = rtc.now();

// //     //Serial.print(now.year(), DEC);
// //     //Serial.print('/');
// //     //Serial.print(now.month(), DEC);
// //     //Serial.print('/');
// //     //Serial.print(now.day(), DEC);
// //     //Serial.print(" (");
// //     //Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
// //     //Serial.print(") ");
// //     //Serial.print(now.hour(), DEC);
// //     //Serial.print(':');
// //     //Serial.print(now.minute(), DEC);
// //     //Serial.print(':');
// //     //Serial.print(now.second(), DEC);
// //     //Serial.println();

// //     //Serial.print(" since midnight 1/1/1970 = ");
// //     //Serial.print(now.unixtime());
// //     //Serial.print("s = ");
// //     //Serial.print(now.unixtime() / 86400L);
// //     //Serial.println("d");

// //     // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
// //     DateTime future (now + TimeSpan(7,12,30,6));

// //     //Serial.print(" now + 7d + 12h + 30m + 6s: ");
// //     //Serial.print(future.year(), DEC);
// //     //Serial.print('/');
// //     //Serial.print(future.month(), DEC);
// //     //Serial.print('/');
// //     //Serial.print(future.day(), DEC);
// //     //Serial.print(' ');
// //     //Serial.print(future.hour(), DEC);
// //     //Serial.print(':');
// //     //Serial.print(future.minute(), DEC);
// //     //Serial.print(':');
// //     //Serial.print(future.second(), DEC);
// //     //Serial.println();

// //     //Serial.print("Temperature: ");
// //     //Serial.print(rtc.getTemperature());
// //     //Serial.println(" C");

// //     //Serial.println();
// //     delay(3000);
// // }

/*
 Chân data của các Module thu kết nối chân 11 của Arduino
 Mở Serial Monitor, chọn No line ending, baud 9600
 Dùng Remote hồng ngoại để kiểm tra tín hiệu
 */

// #include <IRremote.h>

// int RECV_PIN = 11;

// IRrecv irrecv(RECV_PIN);

// decode_results results;

// void setup()
// {
//   Serial.begin(9600);
//   irrecv.enableIRIn(); // Start the receiver
// }

// void loop() {
//   if (irrecv.decode(&results)) {
//     //Serial.println(results.value, HEX);
//     irrecv.resume(); // Receive the next value
//   }
// }
