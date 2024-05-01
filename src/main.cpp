
/////////////CONFIG BLOCK/////////////////
#include <Arduino.h>
#include <SPI.h>
#include "config/variable.h"
#include "config/static_variable.h"
#include "process/ir_process.h"
#include "config/PinDefinitionsAndMore.h"
#include "process/serial_process.h"
#include "process/RTC_process.h"
#include "process/total_process.h"
#include "process/timer_process.h"
#include "data/memsys.h"
#include <fix_fft.h>
memsys KEY_SYS;
#ifndef DEBUG_PRG
#include "data_covert/number_coverter.h"
#include "encoder_process.h"
#include "process/eeprom_process.h"
HardwareSerial SerialPort(1);
#endif // DEBUG
#ifdef TASK_CORE
TaskHandle_t Process_data_task;
#endif //TASK_CORE
#if SERVO_CONTROL
#include <ESP32Servo.h>
Servo myservo[5];
#endif //SERVO_CONTROL
#ifdef RTC_ENABLE
#endif //RTC_ENABLE
#ifdef USE_IR
#include <IRremote.hpp>
#define RAW_BUFFER_LENGTH  600  
#endif // USE_IR
/////////////////////////////////////////////////////////////

///////SYCN SERIAL DATA BLOCK////////////////////////////////

#ifdef SERIAL_CODE_ENABLE

 
#endif //SERIAL_CODE_ENABLE
#if SERIAL_DATA
#endif //SERIAL_DATA_RECEIVE
////////////////////INPUT_BLOCK//////////////////
#ifdef USE_IR
void handleOverflow();
void IR_PROGRAM()
{
    if (DOUBLE_CLICK_FLAG)
    {
        DOUBLE_CLICK_WAIT++;
        if (DOUBLE_CLICK_WAIT > 1)
        {
            DOUBLE_CLICK_WAIT = 0;
            DOUBLE_CLICK_FLAG = 0;
            Serial.print("\nDOUBLE CLICK");
        }
    }
      if (SINGLE_CLICK_FLAG)
    {
        SINGLE_CLICK_WAIT++;
        if (SINGLE_CLICK_WAIT > 1)
        {
            SINGLE_CLICK_WAIT = 0;
            SINGLE_CLICK_FLAG = 0;
            Serial.print("\nSINGLE CLICK");
        }
    }

    if (DOUBLE_CLICK_DETECT)
    {
        if (millis() - CLICK_SAMPLE > 400)
        {
            if (CLICK_COUNTER == 1)
            {
                CLICK_COUNTER = 0;
                SINGLE_CLICK_FLAG = 1;
                
            }
        }
    }
    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW)
        {
            handleOverflow();
        }
        else
        {
            if ((IrReceiver.decodedIRData.protocol != SONY) && (IrReceiver.decodedIRData.protocol != PULSE_WIDTH) && (IrReceiver.decodedIRData.protocol != PULSE_DISTANCE) && (IrReceiver.decodedIRData.protocol != UNKNOWN))
            {
            }
            if (IrReceiver.decodedIRData.protocol != UNKNOWN)
            {
                if (IrReceiver.printIRSendUsage(&Serial))
                {
                    PRESS_FLAG = 1;
                    if (CLICK_COUNTER == 0)
                    {
                        DOUBLE_CLICK_DETECT = 1;
                        CLICK_SAMPLE = millis();
                    }
                    if (CLICK_COUNTER == 1)
                    {
                        CLICK_SAMPLE = millis();
                    }

                    CLICK_COUNTER++;
                    if (CLICK_COUNTER > 1)
                    {
                        DOUBLE_CLICK_FLAG = 1;
                        CLICK_COUNTER = 0;
                        DOUBLE_CLICK_DETECT = 0;
                    }
                }
            }
        }
        IrReceiver.resume();
    }
}
void handleOverflow()
{
    IrReceiver.stopTimer();
    IrReceiver.restartTimer(50000); 
}
void get_ir_data()
{
IR_PROGRAM();
data_IR_COMMAND_CODE = IrReceiver.decodedIRData.command;
if(SINGLE_CLICK_FLAG) {data_IR_COMMAND_TYPE = 1;}
else if (DOUBLE_CLICK_FLAG) {data_IR_COMMAND_TYPE = 2;}
else {data_IR_COMMAND_TYPE = 0;}
}
#endif //USE IR
#if USE_EQ
void get_adc_data()
{

}
#endif //USE EQ
#if USE_PLAYBACK
void get_sw_data()
{
data_SW = sw_stat;
}
#endif //USE_PLAYBACK
#if USE_BPM
void get_bpm_interval_data()
{

}
#endif //USE_BPM

// void get_input_data()
// {
// get_ir_data();
// get_adc_data();
// get_sw_data();
// get_bpm_interval_data();
// }



///////PROCESS_PROGRAM_BLOCK //////////////



// #if TOTAL_PROGRAM

// #endif
#if TIMER_CONTROL_ENABLE

#endif
#if FFT_ENABLE
void FFT_PROGRAM()
{
  int TOTAL_BAND = 0;
  int MIN_ADC = 1024, MAX_ADC = 0;
  int32_t MAX_BAND = 0;
  for (int i = 0; i < 128; i++) 
  {
    L_AUDIO_ANALOG_VALUE = analogRead(MICRO_L_CHANNEL_PIN) - 512;
    R_AUDIO_ANALOG_VALUE = analogRead(MICRO_R_CHANNEL_PIN) - 512; 
    ADC_DATA[i] = val / 4;
    im[i] = 0;
    if (L_AUDIO_ANALOG_VALUE > MAX_ADC)
    {
      MAX_ADC = L_AUDIO_ANALOG_VALUE;
      MAX_ADC_VALUE = MAX_ADC;
    } 
    if (L_AUDIO_ANALOG_VALUE < MIN)
    {
      MIN = L_AUDIO_ANALOG_VALUE;
      MIN_ADC_VALUE = MIN;
    }
  }
  fix_fft(ADC_DATA, im, 7, 1);
  if (millis() - timer_print_band > 50)
  {
    timer_print_band = millis();
    MAX_BAND = 0;
    for (int i = 1; i < 64; i++)
    {
      int dat = sqrt(ADC_DATA[i] * ADC_DATA[i]+ im[i] * im[i]);
      if (dat > MAX_BAND)
      {
        MAX_BAND = dat;
      }
      datak[i] = dat;
    }
    TOTAL_BAND = MAX_BAND;
    if (sample_flag)
    {
      sample_flag = 0;
    }
    else
    {
      sample_flag = 1;
    }
  }
}

void send_eq()
{
  if (millis() - eq_time_sample > 50)
  {
    eq_time_sample = millis();
    for (int i = 0; i < 16; i++)
    {
      uart_ptr(KEY_EQ, i, datak[i]);
    }
  }
}
#endif
#ifdef SILENCE_FINDER_ENABLE

void SILENCE_FINDER_PROGRAM ()
{
  if (compare_enable)
  {
    if (data_sound < 30)
    {
      if (sample_flag != old_sample_flag)
      {
        counter_silence++;
      }
      if (counter_silence > 10)
      {
        counter_silence = 0;
        compare_enable = 0;
        if (!direction)
        {
          track++;
          if (track > 20)
          {
            track = 20;
          }
        }
        else
        {
          track--;
          if (track < 1)
          {
            track = 1;
          }
        }
      }
    }
    else
    {
      counter_silence = 0;
    }
  }
  else
  {
    if (data_sound > 30)
    {
      if (sample_flag != old_sample_flag)
      {
        old_sample_flag = sample_flag;
        counter_non_silence++;
        if (counter_non_silence > 100)
        {
          compare_enable = 1;
          reset_timer_on_relay(1);
          counter_non_silence = 0;
        }
      }
    }
  }
}
#endif // SILENCE_FINDER_ENABLE
#if BUTTON_CONTROL
void button_control_program()
{
  byte _servo;
  if (press_flag != old_press_flag)
  {
    old_press_flag = press_flag;
    _servo = svtag;
    if (press_flag)
    {
      BT_MODE[_servo] = 1;
      press_flag = 0;
    }
  }
  if (!servo_control_enable[_servo])
  {
    if (BT_MODE[_servo])
    {
      BT_MODE[_servo] = 0;
      servo_control_enable[_servo] = 1;
      timer_start_flag[_servo] = 0;
    }
  }
}
#endif //BUTTON_CONTROL
#if SERVO_CONTROL
void servocontrol()
{
  byte _servo = svtag;
  if (servo_control_enable[_servo])
  {
    timer_on_relay(_servo, 500, 0);
    if (timer_flag[_servo])
    {
      if (timer_counter_cycle[_servo] == 0)
      {
        myservo[_servo].write(60);
        if (playback_enable)
        {
          if (_servo == 2)
          {
            digitalWrite(RELAY_PIN, HIGH);
          }
        }
        else
        {

          if (_servo == 2)
          {
            digitalWrite(RELAY_PIN, HIGH);
          }
        }
      }
      if (timer_counter_cycle[_servo] == 1)
      {
        myservo[_servo].write(0);
      }
      timer_counter_cycle[_servo]++;
      if (timer_counter_cycle[_servo] == 2)
      {
        if (playback_enable)
        {
          if (_servo == 2)
          {

            digitalWrite(RELAY_PIN, LOW);
          }
        }
        else
        {

          if (_servo == 2)
          {

            digitalWrite(RELAY_PIN, LOW);
          }
        }

        servo_control_enable[_servo] = 0;
        timer_counter_cycle[_servo] = 0;
        BT_MODE[_servo] = 0;
      }
      timer_start_flag[_servo] = 0;
    }
  }
}
#endif //SERVO_CONTROL
#if AUTO_PLAYBACK
void stop_to_next_button(byte button)
{
  stop_to_press_flag = 1;
  timer_start_flag[13] = 0;
  timer_flag[13] = 0;
  button_stop_wait = button;
}
void button_processing()
{
  if (stop_to_press_flag)
  {
    timer_on_relay(13, 2000, 1);
    if (timer_flag[13])
    {
      uart_ptr("BUTTON", button_stop_wait, 1);
      stop_to_press_flag = 0;
      timer_flag[13] = 0;
    }
  }
}
void wait_to_stop()
{
  if (program_stat)
  {
    if (wait_enable)
    {
      timer_on_relay(11, 2000, 1);
      if (timer_flag[11])
      {
        if (situation == 0)
        {
          uart_ptr("BUTTON", 3, 1);
          stop_to_next_button(2);
        }
        if (situation == 1)
        {
          uart_ptr("BUTTON", 3, 1);
          stop_to_next_button(0);
        }
        if (situation == 2)
        {
          uart_ptr("BUTTON", 3, 1);
          stop_to_next_button(1);
        }

        program_stat = 0;
        wait_enable = 0;
      }
    }
  }
}

void auto_playback_program()
{
  wait_to_stop();
  button_processing();
  if ((current_angle - old_angle3 < 10) && (current_angle - old_angle3 > -10))
  {
    old_angle3 = current_angle;
    encoder_stat = 0;
  }
  else
  {
    if (current_angle > old_angle3)
    {
      calculate_direction = 0;
    }
    else
    {
      calculate_direction = 1;
    }
    encoder_stat = 1;
    old_angle3 = current_angle;
  }
  if (sw_stat != old_sw_stat)
  {
    if (sw_stat)
    {
      sw_enable = 1;
    }
  }
  if (!playback_enable)
  {
    if ((encoder_stat != old_encoder_stat) || (sw_enable))
    {
      sw_enable = 0;
      if (!encoder_stat)
      {
        wait_enable = 1;
        situation = 0;
        reset_timer_on_relay(11);
      }
      else
      {
        wait_enable = 0;
      }
      old_encoder_stat = encoder_stat;
    }
  }
  if ((playback_enable) && (playing_mode))
  {
    if (playback_enable != old_playback_enable)
    {
      old_playback_enable = playback_enable;
      calculate_direction = 0;
    }

    if (encoder_stat != old_encoder_stat)
    {
      if ((!encoder_stat) && calculate_direction)
      {
        wait_enable = 1;
        situation = 1;
        reset_timer_on_relay(11);
      }
      if ((!encoder_stat) && (!calculate_direction))
      {
        if (!stop_flag)
        {
          wait_enable = 1;
          situation = 2;
          reset_timer_on_relay(11);
        }
        stop_flag = 0;
      }
      old_encoder_stat = encoder_stat;
    }
  }
}
#endif //AUTO_PLAYBACK


/// @brief ///////TASK////////////
void Process_data_task_code(void *parameter) {
  //SerialPort.begin(115200, SERIAL_8N1, 18, 19); 
  for(;;) { 
//  Serial_Data_Receive();
  }
    }
//////////////////////////////////



  byte (*_rtc_hrs)() = &RTC_GET_HOUR;
  byte (*_rtc_min)() = &RTC_GET_MINUTE;
  byte (*_rtc_sec)() = &RTC_GET_SECOND;
  bool (*_rtc_flag)() =&RTC_GET_FLAG;
  void (*sendtt)(byte*,byte*,byte*) = &send_total;
  void (*uart)(String*,int*,int32_t*) = &SEND_UART;
/// @brief /////////SETUP//////////////
void setup()
{
  
  

  pinMode(SW_RELAY, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(115200);
  delay(1000);


#ifdef TASK_CORE
  xTaskCreatePinnedToCore(
      Process_data_task_code,   
      "Process_data_task",    
      10000,       
      NULL,        
      0,          
      &Process_data_task,      
      0            
    );
#endif // TASK_CORE
#if SERVO_CONTROL
  myservo[0].attach(5);
  myservo[1].attach(6);
  myservo[2].attach(7);
  myservo[3].attach(8);
  myservo[4].attach(9);

  myservo[0].write(0);
  myservo[1].write(0);
  myservo[2].write(0);
  myservo[3].write(0);
  myservo[4].write(0);
#endif //SERVO_CONTROL
#if USE_IR
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    printActiveIRProtocols(&Serial);
#endif // IR 

#if RTC_ENABLE
  
#endif //RTC_ENABLE
}
/////////////////////////////////////////

void loop()
{ 
  bool k = KEY_SYS.sw_stat();
  
#ifdef USE_IR
IR_PROGRAM();
#endif //USE_IR
#if RTC_ENABLE
#endif //RTC
#if SILENCE_FINDER_ENABLE
SILENCE_FINDER_PROGRAM();
#endif //SILENCE_FINDER_ENABLE
#ifdef ENCODER_SIMULATION 
ENCODER_SIMULATION(&revolution,&current_revolution,&current_angle);
#endif //ENCODER_SIMULATION
#ifdef FFT_ENABLE
FFT_PROGRAM();
#endif



}

