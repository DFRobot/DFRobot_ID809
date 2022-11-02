/*!
 * @file DFRobot_ID809.h
 * @brief Define basic structure of DFRobot_ID809 class
 * @n This is an library for capacitive fingerprint module
 * @n Main functions: fingerprint image capturing, fingerprint comparison, fingerprint deletion
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/cdjq/DFRobot_ID809
 */

#ifndef _DFRobot_ID809_H
#define _DFRobot_ID809_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

#include <stdint.h>

//Open this macro to see the detailed running process of the program 

//#define ENABLE_DBG
#ifdef ENABLE_DBG
#define LDBG(...)  {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define LDBG(...)
#endif

extern Stream *dbg;

  /*
   Frame struct of command packet 
  */
typedef struct{
  uint16_t  PREFIX;
  uint8_t   SID;
  uint8_t   DID;
  uint16_t  CMD;
  uint16_t  LEN;
  uint8_t payload[0];
}__attribute__ ((packed)) sCmdPacketHeader_t, *pCmdPacketHeader_t;

  /*
   Frame struct of response packet 
  */
typedef struct{
  uint16_t  PREFIX;
  uint8_t   SID;
  uint8_t   DID;
  uint16_t  RCM;
  uint16_t  LEN;
  uint16_t  RET;
  uint8_t   payload[0];
}__attribute__ ((packed)) sRcmPacketHeader_t, *pRcmPacketHeader_t;

  


class DFRobot_ID809{
public: 

//#define FINGERPRINT_CAPACITY     80      //Fingerprint module capacity
#define MODULE_SN_SIZE           16      //Module SN length 


#define DELALL                   0xFF    //Delete all fingerprints 

#define CMD_PREFIX_CODE          0xAA55  //Command packet prefix code 
#define RCM_PREFIX_CODE          0x55AA  //Response packet prefix code 
#define CMD_DATA_PREFIX_CODE     0xA55A  //Command data packet prefix code 
#define RCM_DATA_PREFIX_CODE     0x5AA5  //Response data packet prefix code 

#define CMD_TYPE                 0xF0    //Command packet type 
#define RCM_TYPE                 0xF0    //Response packet type 
#define DATA_TYPE                0x0F    //Data packet type 

#define CMD_TEST_CONNECTION      0X0001  //Test connection 
#define CMD_SET_PARAM            0X0002  //Set parameter
#define CMD_GET_PARAM            0X0003  //Read parameter 
#define CMD_DEVICE_INFO          0X0004  //Read device information 
#define CMD_SET_MODULE_SN        0X0008  //Set module serial number 
#define CMD_GET_MODULE_SN        0X0009  //Read module serial number
#define CMD_ENTER_STANDBY_STATE  0X000C  //Enter sleep mode 
#define CMD_GET_IMAGE            0X0020  //Capture fingerprint image 
#define CMD_FINGER_DETECT        0X0021  //Detect fingerprint 
    #define CMD_UP_IMAGE_CODE        0X0022  //Upload fingerprint image to host 
    #define CMD_DOWN_IMAGE           0X0023  //Download fingerprint image to module 
#define CMD_SLED_CTRL            0X0024  //Control collector backlight 
#define CMD_STORE_CHAR           0X0040  //Save fingerprint template data into fingerprint library 
#define CMD_LOAD_CHAR            0X0041  //Read fingerprint in module and save it in RAMBUFFER temporarily  
    #define CMD_UP_CHAR              0X0042  //Upload the fingerprint template saved in RAMBUFFER to host 
    #define CMD_DOWN_CHAR            0X0043  //Download fingerprint template to module designated RAMBUFFER
#define CMD_DEL_CHAR             0X0044  //Delete fingerprint in specific ID range 
#define CMD_GET_EMPTY_ID         0X0045  //Get the first registerable ID in specific ID range 
#define CMD_GET_STATUS           0X0046  //Check if the designated ID has been registered 
#define CMD_GET_BROKEN_ID        0X0047  //Check whether there is damaged data in fingerprint library of specific range
#define CMD_GET_ENROLL_COUNT     0X0048  //Get the number of registered fingerprints in specific ID range 
#define CMD_GET_ENROLLED_ID_LIST 0X0049  //Get registered ID list
#define CMD_GENERATE             0X0060  //Generate template from the fingerprint images saved in IMAGEBUFFER temporarily 
#define CMD_MERGE                0X0061  //Synthesize fingerprint template data 
#define CMD_MATCH                0X0062  //Compare templates in 2 designated RAMBUFFER 
#define CMD_SEARCH               0X0063  //1:N Recognition in specific ID range 
#define CMD_VERIFY               0X0064  //Compare specific RAMBUFFER template with specific ID template in fingerprint library 

#define ERR_SUCCESS              0x00    //Command processed successfully 
#define ERR_ID809                0xFF    //error 


public:
  
  typedef enum{
    eBreathing = 1,  //Breathing 
    eFastBlink,      //Quick blink
    eKeepsOn,        //On
    eNormalClose,    //Off
    eFadeIn,         //Fade in 
    eFadeOut,        //Fade out
    eSlowBlink       //Slow blink
  }eLEDMode_t;
  
  typedef enum{
    eLEDGreen = 1,   //green 
    eLEDRed,         //red 
    eLEDYellow,      //yellow
    eLEDBlue,        //blue
    eLEDCyan,        //cyan
    eLEDMagenta,     //magenta
    eLEDWhite        //white
  }eLEDColor_t;
   
  typedef enum{
    e9600bps = 1,
    e19200bps,
    e38400bps,
    e57600bps,
    e115200bps
  }eDeviceBaudrate_t;
  
  typedef enum{
    eErrorSuccess            = 0x00,    //Command processed successfully
    eErrorFail               = 0x01,    //Command processing failed 
    eErrorVerify             = 0x10,    //1:1 Templates comparison in specific ID failed 
    eErrorIdentify           = 0x11,    //1:N comparison has been made, no same templates here 
    eErrorTmplEmpty          = 0x12,    //No registered template in the designated ID 
    eErrorTmplNotEmpty       = 0x13,    //Template already exists in the specified ID 
    eErrorAllTmplEmpty       = 0x14,    //No registered Template 
    eErrorEmptyIDNoexist     = 0x15,    //No registerable Template ID 
    eErrorBrokenIDNoexist    = 0x16,    //No damaged Template 
    eErrorInvalidTmplData    = 0x17,    //The designated Template Data is invalid 
    eErrorDuplicationID      = 0x18,    //The fingerprint has been registered 
    eErrorBadQuality         = 0x19,    //Poor quality fingerprint image 
    eErrorMergeFail          = 0x1A,    //Template synthesis failed 
    eErrorNotAuthorized      = 0x1B,    //Communication password not authorized 
    eErrorMemory             = 0x1C,    //Error in exernal Flash burning 
    eErrorInvalidTmplNo      = 0x1D,    //The designated template ID is invalid 
    eErrorInvalidParam       = 0x22,    //Incorrect parameter has been used 
    eErrorTimeOut            = 0x23,    //Acquisition timeout 
    eErrorGenCount           = 0x25,    //Invalid number of fingerprint synthesis 
    eErrorInvalidBufferID    = 0x26,    //Wrong Buffer ID value 
    eErrorFPNotDetected      = 0x28,    //No fingerprint input into fingerprint reader 
    eErrorFPCancel           = 0x41,    //Command cancelled 
    eErrorRecvLength         = 0x42,    //Wrong length of recieved data 
    eErrorRecvCks            = 0x43,    //Wrong check code 
    eErrorGatherOut          = 0x45,    //Exceed upper limit of acquisition times 
    eErrorRecvTimeout        = 0x46     //Communication timeout 
  }eError_t;
  
  typedef struct{
    /**< Gesture enumeration variable X */
    eError_t error;
    /**< Description about the gesture enumeration variable X */
    const char * description;
  }sErrorDescription_t;

public:
  DFRobot_ID809();
  ~DFRobot_ID809();
  
  /**
   * @brief Init communication port
   * @param Software serial or hardware serial 
   * @return true or false
   */
  bool begin(Stream &s_);
  
  /**
   * @brief Test whether the module connection is ok
   * @return true or false
   */
  bool isConnected();
  
  /**
   * @brief Set module ID
   * @param ID:1-255
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setDeviceID(uint8_t deviceID);
  
  /**
   * @brief Set module security level 
   * @param security level:1-5
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setSecurityLevel(uint8_t securityLevel);
  
  /**
   * @brief Set module fingerprint replication check (Check whether the fingperint has been registered when saving it)
   * @param 1(ON) or 0(OFF)
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setDuplicationCheck(uint8_t duplicationCheck);
  
  /**
   * @brief Set module baud rate 
   * @param Baudrate:in typedef enum eDeviceBaudrate_t
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setBaudrate(eDeviceBaudrate_t baudrate);
  
  /**
   * @brief Set module self-learning function (Update fingeprint when fingerprint comparison succeeds)
   * @param 1(ON) or 0(OFF)
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setSelfLearn(uint8_t selfLearn);
  
  /**
   * @brief Read module ID
   * @return ID号:1-255 or ERR_ID809
   */
  uint8_t getDeviceID();
  
  /**
   * @brief Read module security level 
   * @return Security level:1-5 or ERR_ID809
   */
  uint8_t getSecurityLevel();
  
  /**
   * @brief Read module fingerprint replication check status
   * @return Status：1(ON), 0(OFF) or ERR_ID809
   */
  uint8_t getDuplicationCheck();
  
  /**
   * @brief Read module baud rate 
   * @return Baudrate:in typedef enum eDEVICE_BAUDRATE_t or ERR_ID809
   */
  uint8_t getBaudrate();
  
  /**
   * @brief Read module self-learning function status 
   * @return Status：1(ON), 0(OFF) or ERR_ID809
   */
  uint8_t getSelfLearn();
  uint8_t getTemplate(uint16_t id,uint8_t * temp);
  uint8_t downLoadTemplate(uint16_t id,uint8_t * temp);
  uint8_t getFingerImage(uint8_t *image);
  uint8_t downLoadImage(uint16_t id,uint8_t * temp);
  uint8_t receiveImageData(uint8_t *image);
  uint8_t getQuarterFingerImage(uint8_t *image);
  uint8_t contrastTemplate(uint8_t *temp);
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
   * @brief Set LED
   * @param mode:in typedef enum eLEDMode_t
   * @param color:in typedef enum eLEDColor_t
   * @param blink Count: 00 represents blinking all the time
   * @This parameter will only be valid in mode eBreathing, eFastBlink, eSlowBlink
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t ctrlLED(eLEDMode_t mode,eLEDColor_t color,uint8_t blinkCount);
  
  /**
   * @brief Detect if there is finger touched 
   * @return 1(Touched) or 0(No touch)
   */
  uint8_t detectFinger();
  
  /**
   * @brief Get the first registerable ID 
   * @return Registerable ID or ERR_ID809
   */
  uint8_t getEmptyID();
  
  /**
   * @brief Check if the ID has been registered 
   * @return 0(Registered), 1(Unregistered) or ERR_ID809
   */
  uint8_t getStatusID(uint8_t ID);
  
  /**
   * @brief Get the number of registered users 
   * @return Number of registered users or ERR_ID809
   */
  uint8_t getEnrollCount();
  
  /**
   * @brief Get registered user list 
   * @return 0(succeed) or ERR_ID809
   */
   uint8_t getEnrolledIDList(uint8_t* list);
  
  /**
   * @brief Fingerprint acquisition 
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t collectionFingerprint(uint16_t timeout,int ramNumber = -1);
  
  /**
   * @brief Save fingerprint 
   * @param Fingerprint ID
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t storeFingerprint(uint8_t ID);
  
  /**
   * @brief Delete fingerprint 
   * @param Delete ID or DELALL(delete all)
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t delFingerprint(uint8_t ID);
  
  /**
   * @brief Match the fingerprint with all fingeprints 
   * @return Successfully matched fingerprint ID, 0(Matching failed) or ERR_ID809
   */
  uint8_t search();

  /**
   * @brief Match the fingerprint with specific fingerprint 
   * @return Successfully matched fingerprint ID, 0(Matching failed) or ERR_ID809
   */
  uint8_t verify(uint8_t ID);

  /**
   * @brief Compare templates in two specific RamBuffers
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
   * @param Fingerprint ID 
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
  
  bool setDbgSerial(Stream &s_){dbg = &s_; return true;}
    uint16_t FINGERPRINT_CAPACITY = 80;
protected:
   /**
   * @brief Set parameter 
   * @param Data type+ data
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t setParam(uint8_t* data);
  
   /**
   * @brief Read parameter 
   * @param Data type 
   * @return data or ERR_ID809
   */
  uint8_t getParam(uint8_t* data);
  
  /**
   * @brief Capture fingerprint image 
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t getImage();
   
   /**
   * @brief Take image as template 
   * @param Ram Buffer number
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t generate(uint8_t RamBufferID);
  
 /**
   * @brief Fingerprint synthesis 
   * @return 0(succeed) or ERR_ID809
   */
  uint8_t merge();
  
 /**
   * @brief Packing data frame 
   * @param Data type：CMD_TYPE or DATA_TYPE
   * @param Command
   * @param Data 
   * @param Length
   * @return Data frame 
   */
  pCmdPacketHeader_t pack(uint8_t type, uint16_t cmd, const char *payload, uint16_t len);
  
 /**
   * @brief Send data 
   * @param Data frame
   */
  void sendPacket(pCmdPacketHeader_t header);
  
 /**
   * @brief Read byte 
   * @param Pointer for saving data 
   * @param Length of data to be received 
   * @return Actual received data length 
   */
  size_t readN(void* buf_, size_t len);
  
 /**
   * @brief Read frame header 
   * @param Frame header struct of response packet
   * @return Response packet type：RCM_TYPE,DATA_TYPE or 1(reading timeout)
   */
  uint16_t readPrefix( pRcmPacketHeader_t header );
  
 /**
   * @brief Read data
   * @param Pointer for saving data 
   * @return 0(success) or ERR_ID809
   */
  uint8_t responsePayload(void* buf);
  
 /**
   * @brief Get command packet CKS
   * @param Command packet frame 
   * @return CKS
   */
  uint16_t getCmdCKS(pCmdPacketHeader_t packet);
  
 /**
   * @brief Get response packet CKS
   * @param Response packet frame 
   * @return CKS
   */
  uint16_t getRcmCKS(pRcmPacketHeader_t packet);
  uint8_t store(uint8_t ID);
  
private:
  Stream *s;
  uint8_t buf[20];     //For saving response packet data 
  pCmdPacketHeader_t  sendHeader;
  pRcmPacketHeader_t  recHeader;
  
  static const sErrorDescription_t /*PROGMEM*/ errorDescriptionsTable[26];   //Error information list 
  
  uint8_t _number = 0;       //Fingerprint acquisistion times 
  uint8_t _state = 0;        //Collect fingerprint state
  eError_t _error;           //Error code 
  uint16_t _PacketSize = 0;  //Data packet length to be sent 
};

#endif


