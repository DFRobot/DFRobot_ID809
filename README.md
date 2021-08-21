# DFRobot_ID809
This capacitive fingerprint sensor supports fingerprint capture, image processing, fingerprint storage, fingerprint comparison and so on.
Taking ID809 high-performance processor and semiconductor fingerprint sensor as the core, the sensor adopts built-in IDfinger6.0 algorithm, which can complete all fingerprint identification work independently.<br>

The product supports UART communication. When working with Arduino library, it can easily realize functions like  fingerprint registration, fingerprint deletion, etc.<br>

This fingerprint sensor comes with round breathing LEDs and has a simple structure, small size, and delicate appearance. The sensor offers fast recognition speed and high security. What’s more, it supports 360-degree arbitrary angle recognition and deep self-learning function, high performance and low power consumption.

   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

1. Fingerprint Registration <br>
2. Fingerprint Matching <br>
3. Fingerprint Deletion <br>
4. Supports for sleep mode <br>

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
  /**
   * @brief Init communication serial port
   * @param Hardware serial or Software serial
   * @return true or false
   */
  bool begin(Stream &s_);

  /**
   * @brief Test whether the module is properly connected 
   * @return true or false
   */
  bool isConnected();
  
  /**
   * @brief Set module ID
   * @param ID number:1-255
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setDeviceID(uint8_t deviceID);
  
  /**
   * @brief Set module security level
   * @param Security level:1-5
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setSecurityLevel(uint8_t securityLevel);
  
  /**
   * @brief Set module fingerprint duplication check(check whether the fingerprint has been registrated already when saving it)
   * @param 1(ON) or 0(OFF)
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setDuplicationCheck(uint8_t duplicationCheck);
  
  /**
   * @brief Set module baud rate
   * @param Baudrate:in typedef enum eDEVICE_BAUDRATE_t
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setBaudrate(eDeviceBaudrate_t baudrate);
  
  /**
   * @brief Set module self-learning function(update fingerprint when fingerprint comparison succeeds)
   * @param 1(ON) or 0(OFF)
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setSelfLearn(uint8_t selfLearn);
  
  /**
   * @brief Read module ID
   * @return ID number:1-255 or ERR_ID809
   */
  uint8_t getDeviceID();
  
  /**
   * @brief Read module security level
   * @return Security level:1-5 or ERR_ID809
   */
  uint8_t getSecurityLevel();
  
  /**
   * @brief Read the fingerprint dupilcation check status of module 
   * @return Status：1(ON), 0(OFF) or ERR_ID809
   */
  uint8_t getDuplicationCheck();
  
  /**
   * @brief Read module baud rate
   * @return Baudrate:in typedef enum eDEVICE_BAUDRATE_t or ERR_ID809
   */
  uint8_t getBaudrate();
  
  /**
   * @brief Read the module self-learning function status 
   * @return Status：1(ON), 0(OFF) or ERR_ID809
   */
  uint8_t getSelfLearn();
   
  /**
   * @brief Read device number 
   * @return Device number
   */
  String getDeviceInfo();
  
  /**
   * @brief Set serial number 
   * @param String pointer 
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setModuleSN(const char* SN);
  /**
   * @brief Read serial number
   * @return Serial number
   */
  String getModuleSN();
  
  /**
   * @brief Set LED light
   * @param mode:in typedef enum eLED_MODE_t
   * @param color:in typedef enum eLED_COLOR_t
   * @param blink Count 0 represents keeping breathing, blinking, this parameter is only valid in mode eBreathing, eFastBlink, eSlowBlink
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t ctrlLED(eLEDMode_t mode,eLEDColor_t color,uint8_t blinkCount);
  
  /**
   * @brief Detect whether the module is touched by a finger 
   * @return 1(Yes) or 0(No)
   */
  uint8_t detectFinger();
  
  /**
   * @brief Get first registrable ID number 
   * @return Registrable ID number or Error Code
   */
  uint8_t getEmptyID();
  
  /**
   * @brief Check whether the ID has been registered
   * @return 0(Registered), 1(Not yet) or ERR_ID809
   */
  uint8_t getStatusID(uint8_t ID);
  
  /**
   * @brief Get the number of registered users 
   * @return Number of registered users or ERR_ID809
   */
  uint8_t getEnrollCount();
  
  /**
   * @brief Get the list of registered users 
   * @return 0(succeed) or ERR_ID809
   */
   uint8_t getEnrolledIDList(uint8_t* list);
  
  /**
   * @brief Capture fingerprint
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t collectionFingerprint(uint16_t timeout);
  
  /**
   * @brief Save fingerprint
   * @param Fingerprint ID
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t storeFingerprint(uint8_t ID);
  
  /**
   * @brief Delete fingerprint 
   * @param Finerprint ID or DELALL(delete all)
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t delFingerprint(uint8_t ID);
  
  /**
   * @brief Match the fingerprint with all fingerprints
   * @return Successfully matched fingerprint ID, 0(Finerprint matching failed) or ERR_ID809
   */
  uint8_t search();

  /**
   * @brief Match the fingerprint with a designated fingerprint
   * @return Successfully matched fingerprint ID, 0(Finerprint matching failed) or ERR_ID809
   */
  uint8_t verify(uint8_t ID);

  /**
   * @brief Compare two designated RamBuffer templates 
   * @param RamBuffer number
   * @param RamBuffer number
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t match(uint8_t RamBufferID0, uint8_t RamBufferID1);
  
  /**
   * @brief Get the number of damaged fingerprints 
   * @return Damaged fingerprint ID or ERR_ID809
   */
  uint8_t getBrokenQuantity();

  /**
   * @brief Get the first damaged fingerprint ID 
   * @return Damaged fingerprint ID or ERR_ID809
   */
  uint8_t getBrokenID();
  
  /**
   * @brief Take out fingerprint template, temporarily save into RamBuffer
   * @param Fingerprint ID number
   * @param RamBuffer number 0-2
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t loadFingerprint(uint8_t ID, uint8_t RamBufferID);
  
  /**
   * @brief Enter Standby mode
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t enterStandbyState();
  
  /**
   * @brief Get error information
   * @return Text description of error information
   */
  String getErrorDescription();
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |         √    |              |             | Compatibility is not so good currently
ESP8266        |         √    |              |             | Compatibility is not so good currently
FireBeetle M0      |         √    |              |             | 



## History

- Data 2020-3-26
- Version V0.1


## Credits

Written by(Eddard.liu@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))





