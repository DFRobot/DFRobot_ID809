//获取指纹的图像，1.显示在屏幕上
//现象：
//setup
//loop
//1.按下手指采集指纹图像
//2.显示图像
//需要下载DFRobot_GDL.h库
#include <DFRobot_ID809.h>
#include "DFRobot_GDL.h"
//Custom communication pins
/*M0*/
#if defined ARDUINO_SAM_ZERO
#define TFT_DC  7
#define TFT_CS  5
#define TFT_RST 6
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC  D7
#define TFT_CS  D8
#define TFT_RST D9
/* AVR series mainboard */
#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#endif

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
DFRobot_ILI9341_240x320_HW_SPI  screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//String desc;
//DFRobot_ID809 fingerprint;
//String desc;
uint8_t data[6400];

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

  fingerprint.begin(FPSerial);
  screen.begin();
  screen.fillScreen(0xf800);
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
  
}

void loop(){
  //设置采集灯环
  fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  Serial.println("请按下手指");
   //采集图像
   fingerprint.getQuarterFingerImage(data);
   //显示图像
   //
   for(uint16_t i = 0; i < 6400 ;i++){
     uint8_t a = i % 80;
     uint8_t b = i / 80;
     screen.drawPixel(80+a,120+b,(data[i]/4)<<5);
  
   }
}