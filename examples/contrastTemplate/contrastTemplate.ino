/*!
 *@file contrastTemplate.ino
 *@brief Extract the ID 1 fingerprint template, and collect fingerprint to compare with it.
 *@copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 *@licence     The MIT License (MIT)
 *@author [fengli](li.feng@dfrobot.com)
 *@version  V1.0
 *@date  2021-6-01
 *@get from https://www.dfrobot.com
 *@https://github.com/DFRobot/DFRobot_ID809
*/
#include <DFRobot_ID809.h>


uint8_t temp[1008]={0};    //Template data

/*Use software serial when using UNO or NANO*/
#if ((defined ARDUINO_AVR_UNO) || (defined ARDUINO_AVR_NANO))
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(2, 3);  //RX, TX
    #define FPSerial Serial1
#else
    #define FPSerial Serial1
#endif

DFRobot_ID809 fingerprint;
//String desc;

void setup(){
  /*Init print serial port */
  Serial.begin(9600);
  /*Init FPSerial*/
  FPSerial.begin(115200);
  /*Take FPSerial as communication port of fingerprint module */
  fingerprint.begin(FPSerial);
  /*Wait for Serial to open*/
  while(!Serial);
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
  //Get the fingerprint template of ID 1
  fingerprint.getTemplate(/*id = */1,temp);
  //Download the template to ID 1.
  //fingerprint.downLoadTemplate(/*id = */1,temp);
}

void loop(){
  /*Set the fingerprint LED ring as blue breathing light*/
  fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  Serial.println("Please press down your finger");
  /*Capture fingerprint image, Disable the collection timeout function 
    If succeed return 0, otherwise return ERR_ID809
    Collect fingerprint template data and store them to rambuffer0
   */
  if((fingerprint.collectionFingerprint(/*timeout=*/0,0)) != ERR_ID809){
    /*Set fingerprint LED ring to quick blink in yellow 3 times*/
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDYellow, /*blinkCount = */3);
    Serial.println("Capturing succeeds");
    Serial.println("Please release your finger");
    /*Wait for finger to release
      Return 1 when finger is detected, otherwise return 0 
     */
    while(fingerprint.detectFinger());
    //Compare the template data with the collected fingerprints
    if(!fingerprint.contrastTemplate(/*TEMP = */temp)){
      /*Set fingerprint LED ring to always ON in green*/
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
      Serial.println("Matching succeeds, the template matches the finger");
    }else{
      /*Set fingerprint LED ring to always ON in red*/
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */0);
      Serial.println("Matching fails, the template does not match the finger");
    }
  }else{
    Serial.println("Capturing fails");
  }
  Serial.println("-----------------------------");
  delay(1000);
}
