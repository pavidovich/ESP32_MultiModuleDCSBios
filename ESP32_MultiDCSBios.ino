/*
 * ESP32 Dev Module
 * Default 4MB with spiffs
 * 
 */

#define ESP32

#include "include.h"
#include "NetConfig.h"
#include "MultiDCSBios.h"

#include "T45_functions.h"
#include "A4EC_functions.h"
#include "F5E3_functions.h"

//**************************
//  LAN definitions
//**************************

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#endif
#ifdef ESP32
  #include <WiFi.h>
#endif

#include <WiFiUdp.h>

WiFiUDP udp;
IPAddress ipmulti(239,255,50,10);
unsigned int multi_port=5010;
unsigned int dcs_port=7778;
char dataUdP[512];

const char* ssid     = "SSID_LAN";
const char* password = "PASS_LAN";
  
IPAddress remote_IP;
IPAddress local_IP;

//**********************
// General
//**********************

MultiDCSBios multiDCS;

moduleActionsReceived moduleActionsReceived[]={
    // Module, Num_Actions, Set_of_Actions
    {A_4E_C,1,A4EC_ActionsReceived},
    {T_45  ,3,T45_ActionsReceived},
    {F_5E_3,3,F5E3_ActionsReceived}
};


moduleActionsToDo moduleSetToDo[]={
    {A_4E_C,A4EC_ActionsToDo},
    {T_45, T45_ActionsToDo},
    {F_5E_3,F5E3_ActionsToDo}
};


void setup() {
  Serial.begin(115200);
  
  // Init LAN
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }

  Serial.print("LAN OK - IP:");
  Serial.println(WiFi.localIP());
  
  local_IP = WiFi.localIP(); 
  
  // multicast listener
  #ifdef ESP8266
    udp.beginMulticast(local_IP,ipmulti,multi_port);
  #endif
  #ifdef ESP32
    udp.beginMulticast(ipmulti,multi_port);
  #endif
  
  multiDCS.setModuleActionsReceived(moduleActionsReceived);
 
}

void loop() {
  // Read Package if available
  
  uint8_t column = 0;
  char dataRead;
 
  if(udp.parsePacket()) {
    unsigned int loc=0;
    while (udp.available()) {
      dataRead = (char) udp.read();
      multiDCS.processChar(dataRead);
    }
  }  

 if (multiDCS.moduleChanged()) {
    Serial.print("\nModule Id:");
    Serial.print(multiDCS.getModuleId(),HEX);
    Serial.print('(');
    Serial.print(multiDCS.getModuleIdSetLoc());
    Serial.print(")\n");
    //moduleChanged=false;
  }


 if (Serial.available()){
   // Send commands to the ESP32 as it was button press
   unsigned char button = Serial.parseInt();
   Serial.print("Module get:");
   Serial.println(multiDCS.getModuleIdSetLoc());
   Serial.print(" button:");
   Serial.print(button);
   moduleExecuteButtonAction(multiDCS.getModuleIdSetLoc(),button);
 }

}

boolean moduleExecuteButtonAction(unsigned int moduleIdSetLoc, unsigned char button){
  udp.beginPacket(udp.remoteIP(),dcs_port);
  uint8_t pos=1;
  char data = moduleSetToDo[moduleIdSetLoc].actionSet[button][0];
  if (data=='-'){
    return false;
  } else { // This button has not any command to send
      while (data!=0x00){       
        udp.write(data);
        data = moduleSetToDo[moduleIdSetLoc].actionSet[button][pos++];
      };
      udp.write('\n');
      udp.endPacket();
      return true; // Command has been sent
  }
  return false;
}
