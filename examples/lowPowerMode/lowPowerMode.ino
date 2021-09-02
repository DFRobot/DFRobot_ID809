/*!
 * @file Demo for low power mode.ino
 * @brief Control Pin VIN via relay to let the Fingerprint module enter low power mode 
 * @n Experiment Phenomenon：If there is no finger pressing for 10s, the mdoule enters sleep mode. Press your finger on the sensor to exit the sleep mode and the light ring turns on. 
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2021-08-20
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_ID809
*/
#include <DFRobot_ID809.h>

#define IRQ    6
#define RELAY  7

/*Use software serial when using UNO or NANO*/
#if ((defined ARDUINO_AVR_UNO) || (defined ARDUINO_AVR_NANO))
    #include <SoftwareSerial.h>
    SoftwareSerial Serial1(2, 3);  //RX, TX
    #define FPSerial Serial1
#else
    #define FPSerial Serial1
#endif

DFRobot_ID809 fingerprint;

long long curr = 0;
uint8_t sleepFlag = 1;

void setup(){
  /*Init print serial port */
  Serial.begin(9600);
  /*Init FPSerial*/
  FPSerial.begin(115200);
  /*Take FPSerial as communication port of fingerprint module */
  fingerprint.begin(FPSerial);
  /*Wait for Serial to open*/
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  delay(100);  //Delay 100ms to wait for the start of the module
  while(!Serial);
  /*Test whether device can communicate properly with mainboard 
    Return true or false
    */
  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");
    delay(1000);
  }
  Serial.println("Module init succeeds, enter sleep mode when no finger pressed for 10s");
  fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
}


void loop(){
  if(digitalRead(IRQ) && (sleepFlag == 0)){
    digitalWrite(RELAY, HIGH);
    Serial.println("Exit sleep mode");
    delay(100);  //Delay 100ms to wait for the start of the module
    curr = millis();
    sleepFlag = 1;
    if(fingerprint.isConnected() == true){
      Serial.println("Module communication back to normal");
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
    } else{
      Serial.println("Module communication recovery failed");
    }
  }
  if((sleepFlag == 1)&&(millis() - curr > 10000)){
    fingerprint.enterStandbyState();  //Let your module enter standby module first, then disconnect VIN power 
    digitalWrite(RELAY, LOW);
    sleepFlag = 0;
    Serial.println("Enter sleep mode");
  }
}
