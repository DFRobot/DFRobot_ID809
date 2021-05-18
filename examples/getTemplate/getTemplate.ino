/*!
 * @file getTemplate.ino
 * @brief Get fingerprint module information 
 * @n Experiment Phenomenon：serial print module ID, security level, baud rate, etc. 
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/cdjq/DFRobot_ID809
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
//DFRobot_ID809_UART fingerprint(115200);
//String desc;
uint8_t data[1024]={0};
void setup(){
  /*Init print serial port */
  Serial.begin(9600);
  /*Init FPSerial*/
  FPSerial.begin(115200);
  /*Take FPSerial as communication port of fingerprint module */
  fingerprint.begin(FPSerial);

  /*Wait for Serial to open*/
  /*Test whether device can communicate properly with mainboard 
    Return true or false
    */
  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");
    /*Get error code information */
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
    delay(1000);
  }
  
  Serial.println("start");
  fingerprint.getTemplate(1,data+1);
  for(uint16_t i = 1 ;i<1024;i++){
    Serial.print(data[i],HEX);
    Serial.print(" ");
   if(i%8 == 0  &&  i!= 0){
    Serial.println();
   }


  }
}

uint8_t enrollCount;   //Number of registered users 

void loop(){


  delay(1000);
}
