/*!
 * @file fingerprintDeletion.ino
 * @brief Delete specific fingerprint 
 * @n Experiment phenomenon：check if the ID has been registered, delete it if it is 
                Prompt "ID is unregistered" if it is not 
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/cdjq/DFRobot_ID809
*/
#include <DFRobot_ID809.h>

#define FINGERPRINTID 1   //The fingerprint ID to be deleted 

/*Use software serial when using UNO or NANO */
#if ((defined ARDUINO_AVR_UNO) || (defined ARDUINO_AVR_NANO))
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(2, 3);  //RX, TX
    #define FPSerial Serial1
#else
    #define FPSerial Serial1
#endif

DFRobot_ID809 fingerprint;
String desc;

void setup(){
  /*Init print serial port*/
  Serial.begin(9600);
  /*Init FPSerial*/
  FPSerial.begin(115200);
  /*Take FPSerial as communication serial port of the fingerprint module */
  fingerprint.begin(FPSerial);
  /*Wait for Serial to open*/
  while(!Serial);
  /*Test whether the device can properly communicate with mainboard
    Return true or false
    */
  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");
    /*Get error code information*/
    desc = fingerprint.getErrorDescription();
    Serial.println(desc);
    delay(1000);
  }
}

void loop(){
  /*Check whether the fingerprint ID has been registered 
    Return 1 if registered, otherwise return 0 
   */
  if(fingerprint.getStatusID(/*Fingerprint ID = */FINGERPRINTID)){
    Serial.println("ID has been registered");
    /*Delete the fingerprint of this ID*/
    fingerprint.delFingerprint(/*Fingerprint ID = */FINGERPRINTID);
    //fingerprint.delFingerprint(DELALL);  //Delete all fingerprints 
    Serial.println("ID has been deleted");
  }else{
    Serial.println("ID is unregistered");
  }
  Serial.println("-----------------------------");
  delay(1000);
}