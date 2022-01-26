/*
 * ESP32 Dev Module
 * or
 * ESP8266 NodeMCU
 * 
 * it can be also tested in other platforms
 * 
 */

// First select the board to use
#define ESP32
//#define ESP8266

#include "include.h"
#include "MultiDCSBios.h"

#include "T45_functions.h"
#include "A4EC_functions.h"
#include "F5E3_functions.h"

//**************************
//  LAN definitions
//**************************

#ifdef ESP32
   #include <WiFi.h>
 #else 
   #include <ESP8266WiFi.h>
#endif

#include <WiFiUdp.h>

WiFiUDP udp;
IPAddress ipmulti(239,255,50,10);
unsigned int multi_port=5010;
unsigned int dcs_port=7778;
char dataUdP[512];


// Remember to add the SSID/PASS
//const char* ssid     = "SSID_LAN";
//const char* password = "PASS_LAN";
  
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

 // This part of the code simulates the button Id obtained from
 // the button box
 int button = getButton();
 
 if (button!=-1 && multiDCS.getModuleId()!=NO_MODULE) {
   moduleExecuteButtonAction(multiDCS.getModuleIdSetLoc(),button);
 }
 
}

int getButton(){
   // this function will simulate a button box and it returns 
   // the code of the button pressed
   // Buttons are in the range of 0..127
   // It returns -1 if there is nothing to return
   // Button Id is set by the Serial monitor
   if (Serial.available()){
      int button = Serial.parseInt();
      if (button>=0 && button <128) {
        return(button);
      }  
   }
   return -1;
}

boolean moduleExecuteButtonAction(unsigned int moduleIdSetLoc, int button){
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
