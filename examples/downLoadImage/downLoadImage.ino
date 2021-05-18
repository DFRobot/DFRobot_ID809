/*!
 * @file downLoadImage.ino
 * @brief 下载指纹图像到传感器中，并转化为模板用于识别
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/cdjq/DFRobot_ID809
*/
#include <DFRobot_ID809.h>
//需要在此放指纹图像的位图数据
//位图颜色深度为256灰度位图,像素为160x160
uint8_t temp[160*160]={0};

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
uint8_t data[1024]={0};
void setup(){
  /*Init print serial port */
  Serial.begin(9600);
  /*Init FPSerial*/
  #ifdef  ESP_PLATFORM 
    FPSerial.begin(115200, SERIAL_8N1, /*rx =*/D3, /*tx =*/D4);
  /*Take FPSerial as communication port of fingerprint module */
  #else
    FPSerial.begin(115200);
  #endif
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
  
  
  fingerprint.downLoadImage(5,temp);
  Serial.println("over");
}

uint8_t enrollCount;   //Number of registered users 

void loop(){


  delay(1000);
}