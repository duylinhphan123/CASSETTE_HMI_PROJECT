#include <Arduino.h>
void send_total(byte* _total_hrs,byte* total_minute,byte* total_second);
void SEND_UART(String* _Sname, int* _Stag, int32_t* _Svalue);
void Serial_Data_Receive();
void showNewData();
void recvWithStartEndMarkers();
void uart_send_clock(byte _hrs, byte _min, byte _sec);
void uart_send_eq();
void uart_send_encoder(int32_t _angle,int32_t _revo);
void uart_send_total_play(byte _hrs, byte _min, byte _sec);
void uart_send_cue_point();
void uart_send_ir_command();
void uart_send_mode();
void uart_send_encoder_state();
