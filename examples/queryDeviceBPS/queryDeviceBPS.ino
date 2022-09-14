/*!
 * @file queryDeviceBPS.ino
 * @brief Query device baud rate
 * @n Experiment Phenomenon：Query device baud rate, and print from serial port 
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_ID809
*/
#include <DFRobot_ID809.h>

/*Use software serial when using UNO or NANO*/
#if ((defined ARDUINO_AVR_UNO) || (defined ARDUINO_AVR_NANO))
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(2, 3);  //RX, TX
    #define FPSerial Serial1
#else
    #define FPSerial Serial1
#endif

DFRobot_ID809 fingerprint;

uint32_t ID809_BPS[5] = {9600, 19200, 38400, 57600, 115200};
uint8_t i = 0;

void setup(){
  /*Init print serial port */
  Serial.begin(9600);
  /*Test module baud rate */
  FPSerial.begin(ID809_BPS[i]);
  Serial.print(".");
  while(fingerprint.begin(FPSerial) == false){
    i++;
    FPSerial.begin(ID809_BPS[i]);
    Serial.print(".");
  }
  Serial.println(" ");
}

void loop(){
  Serial.print("Module baud rate:");
  Serial.println(ID809_BPS[i]);
  Serial.println("-----------------------------");
  delay(1000);
}
