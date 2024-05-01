#include "process/serial_process.h"
extern void (*uart)(String,int,int32_t);
extern boolean newData;
extern String header;
extern char* KEY_RESETCUE;

extern char*KEY_TRACK; 
extern char*KEY_ENCODER;
extern char*KEY_CLOCK;
extern char*KEY_BUTTON;
extern char*KEY_COMMAND;
extern char*KEY_CUEPOINT;
extern char*KEY_EQ;
extern char*KEY_TONE;
extern char*KEY_TOTAL;
extern char*KEY_MODE;
extern char*KEY_REVOLUTION;
extern char*KEY_RESET;
extern char*KEY_REPLAY;
extern char*KEY_MOTOR;
extern char*KEY_PLAYSET;
extern char*KEY_PLAYMODE;
extern int32_t pos;
extern byte numChars;
extern char* receivedChars;
extern char* receivedChars2;
extern char* receivedChars3;
extern void (*sendtt)(byte*,byte*,byte*);
byte _old_sec = 0;
byte _old_min = 0;
byte _old_hrs = 0;
byte _old_ttsec = 0;
byte _old_ttmin = 0;
byte _old_tthrs = 0;
int32_t _old_angle = 0;
int32_t _old_revo = 0;
//extern void (*uart_ptr)(String*,int*,int32_t*);
extern int tag;
#define _KEY_TOTAL  "TT"
// extern void Eeprom24C::write_1_byte(unsigned int address, byte data)

#define CLOCK_HOUR 0
#define CLOCK_MINUTE 1
#define CLOCK_SECOND 2
#define ENCODER_ANGLE 0
#define ENCODER_REVO 1
void SEND_UART(String _Sname, int _Stag, int32_t _Svalue)
{
  Serial.print("<");
  Serial.print(_Sname);
  Serial.print("|");
  Serial.print(_Stag);
  Serial.print("#");
  Serial.print(_Svalue);
  Serial.print(">");
}

void send_total(byte* _total_hrs,byte* _total_minute,byte* _total_second)
{
      uart(_KEY_TOTAL, 0, *_total_hrs);
      uart(_KEY_TOTAL, 1, *_total_minute);
      uart(_KEY_TOTAL, 2, *_total_second);
      uart(_KEY_TOTAL, 3, 0);
}
// void get_send_pointer()
// {
//  void (*sendtt)(byte*,byte*,byte*) = &send_total;
// }
void showNewData()
{
  if (newData == true)
  {
      if(header == KEY_RESETCUE)
      {

      }
    newData = false;
  }
}

void recvWithStartEndMarkers()
{
  static boolean recvInProgress = false;
  static boolean rc_counter_start = false;
  static boolean rc_value_start = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char midMarker = '|';
  char midMarker2 = '#';
  char rc;
  static byte ndk = 0;
  static byte ndk2 = 0;
  while (Serial.available() > 0 && newData == false)
  {
    rc = Serial.read();
    if (recvInProgress == true)
    {
      if (rc != endMarker)
      {
        if (!rc_counter_start)
        {
          if (rc != midMarker)
          {
            receivedChars2[ndk] = rc;
            ndk++;
            if (ndk >= numChars)
            {
              ndk = numChars - 1;
            }
          }
          else
          {
            receivedChars2[ndk] = '\0';
            String headercovert(receivedChars2);
            header = headercovert;
            rc_counter_start = 1;
          }
        }
        else
        {
          if (!rc_value_start)
          {
            if (rc != midMarker2)
            {
              receivedChars3[ndk2] = rc;
              ndk2++;
              if (ndk2 >= numChars)
              {
                ndk2 = numChars - 1;
              }
            }
            else
            {
              receivedChars3[ndk2] = '\0';
              tag = atoi(&receivedChars3[0]);
              rc_value_start = 1;
            }
          }
          else
          {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars)
            {
              ndx = numChars - 1;
            }
          }
        }
      }
      else
      {
        rc_counter_start = 0;
        rc_value_start = 0;
        receivedChars[ndx] = '\0'; // terminate the string
        pos = atoi(&receivedChars[0]);
        recvInProgress = false;
        ndx = 0;
        ndk = 0;
        ndk2 = 0;
        newData = true;
      }
    }
    if (rc == startMarker)
    {
      recvInProgress = true;
    }
  }
}
void Serial_Data_Receive()
{
  showNewData();
  recvWithStartEndMarkers();
}
void uart_send_clock(byte _hrs, byte _min, byte _sec)
{
if(_sec != _old_sec)
{
  uart(KEY_CLOCK,CLOCK_SECOND,_sec);
  uart(KEY_CLOCK,CLOCK_MINUTE,_min);
  uart(KEY_CLOCK,CLOCK_HOUR,_hrs);
  _old_sec = _sec;
}
}
void uart_send_encoder(int32_t _angle, int32_t _revo)
{
  if(_angle != _old_angle)
  {
    _old_angle = _angle;
    uart(KEY_ENCODER,ENCODER_ANGLE,_angle);
  }
 if(_revo != _old_revo)
  {
    _old_revo = _revo;
    uart(KEY_ENCODER,ENCODER_REVO,_revo);
  }

}
