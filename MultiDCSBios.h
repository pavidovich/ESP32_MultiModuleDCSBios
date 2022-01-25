#include <Arduino.h>
#include "Module_Address.h"
#include "include.h"
#include "NetConfig.h"

class MultiDCSBios {
  private:
    unsigned int _moduleId;
    unsigned int _lastModuleId;
    bool _moduleChanged;
    unsigned char _moduleIdSetLoc;

    char _messageDCS[512];
    //char dataIn[];
    
    moduleActionsReceived* _moduleSetReceived;
        
  public:

    MultiDCSBios(){
      _moduleId = NO_MODULE;
      _lastModuleId = NO_MODULE;
      _moduleChanged = false;
      _moduleIdSetLoc = 0;
      memset(_messageDCS,0x00,sizeof(_messageDCS));
    }
    

    unsigned int getModuleId(){
      return _moduleId;
    }
    unsigned char getModuleIdSetLoc(){
      return _moduleIdSetLoc;
    }
    
    bool moduleChanged(){
      // If changed the flag is reset when asked about it
      if (_moduleChanged) {
        _moduleChanged=false;
        return true;
      }
      return false;
    }

    

    void setModuleActionsReceived(moduleActionsReceived* moduleSetReceived){
       _moduleSetReceived =  moduleSetReceived;
    }
    void setMessage(char *dataIn){
      
    }
    
    void processChar(unsigned char c) {
      static unsigned int state=DCSBIOS_STATE_WAIT_FOR_SYNC;
      static unsigned int sync_byte_count=0;
      static unsigned int len=0;
      static unsigned int count=0;
      static unsigned int address=0;
        
          switch(state) {
            case DCSBIOS_STATE_WAIT_FOR_SYNC:
              /* do nothing */
              break;
              
            case DCSBIOS_STATE_ADDRESS_LOW:
              address = (unsigned int)c;
              state = DCSBIOS_STATE_ADDRESS_HIGH;
              break;
              
            case DCSBIOS_STATE_ADDRESS_HIGH:
              address = ( c << 8) | address;
              if (address != 0x5555) {
                state = DCSBIOS_STATE_COUNT_LOW;
                /*Serial.print("\nAddress[");
                Serial.print(address);
                Serial.print("](");*/
              } else {
                state = DCSBIOS_STATE_WAIT_FOR_SYNC;
                address=0;
                len=0;
              }    
              break;
              
            case DCSBIOS_STATE_COUNT_LOW:
              count = (unsigned int)c;
              state = DCSBIOS_STATE_COUNT_HIGH;
              break;
              
            case DCSBIOS_STATE_COUNT_HIGH:
              count = (c << 8) | count;
              state = DCSBIOS_STATE_DATA_LOW;
              
              /*Serial.print(count);
              Serial.print(")");*/
              
              break;
              
            case DCSBIOS_STATE_DATA_LOW:
              //data = (unsigned int)c;
              count--;
              _messageDCS[len]=c;
              len++;
              state = DCSBIOS_STATE_DATA_HIGH;
              break;
              
            case DCSBIOS_STATE_DATA_HIGH:
              //data = (c << 8) | data;
              count--;
              _messageDCS[len]=c;
              len++;
             // Serial.print(data,HEX);
             // Serial.print(" ");
        
              //address += 2;
              if (count == 0) {
                //processData(_messageDCS,address, len);
                processData(address, len);
                len=0;
                address=0;
                state = DCSBIOS_STATE_ADDRESS_LOW;
              } else {
                  state = DCSBIOS_STATE_DATA_LOW;
                }
              break;
            } // END switch(state) 
        
            if (c == 0x55)
              sync_byte_count++;
             else
               sync_byte_count = 0;
               
            if (sync_byte_count == 4) {
              state = DCSBIOS_STATE_ADDRESS_LOW; // Start processing data
              sync_byte_count = 0;
              address=0;
              len=0;
            }
      
    }
    
    void processData(unsigned int address, unsigned int len){//char *messageDCS, unsigned int address, unsigned int len){

      /*Serial.print("Address:");
      Serial.println(address);*/
      
      switch (address){
        case MODULE_NAME:
          if (!strcmp(_messageDCS,"A-4E-C")){
            _moduleId=A_4E_C;
            _moduleIdSetLoc=A4EC_LOC; 
          } else if (!strcmp(_messageDCS,"T-45")){
            _moduleId=T_45;
            _moduleIdSetLoc=T45_LOC;
          } else if (!strcmp(_messageDCS,"AJS37")){
            _moduleId=AJS37;
            _moduleIdSetLoc=AJS37_LOC;
          } else if (!strcmp(_messageDCS,"A-10C")){
            _moduleId=A_10C;
            _moduleIdSetLoc=A10C_LOC;
          } else if (!strcmp(_messageDCS,"F-5E-3")){
            _moduleId=F_5E_3;
            _moduleIdSetLoc=F5E3_LOC;
          }
          if (_moduleId!=_lastModuleId) {
            _moduleChanged=true;
            _lastModuleId=_moduleId;
          }
          break;
        case DCS_BIOS_VERSION:
        case PILOT_NAME:
        case MISSION_START_TIME:
        default:
          executeAction(address, len);
          break;
      }
    }

  void executeAction(unsigned int address, unsigned int len){
    if (_moduleId!=NO_MODULE) {
      unsigned char actions= _moduleSetReceived[_moduleIdSetLoc].numActions;
      for (unsigned char it=0;it<actions;it++){
        if (_moduleSetReceived[_moduleIdSetLoc].actionSet[it].address==address){
          unsigned int mask = _moduleSetReceived[_moduleIdSetLoc].actionSet[it].mask;
          unsigned char shift = _moduleSetReceived[_moduleIdSetLoc].actionSet[it].shift;
          _moduleSetReceived[_moduleIdSetLoc].actionSet[it].callback(_messageDCS, len, mask, shift);
          return;
        }
      }
  } 
}
};
