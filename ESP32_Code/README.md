# ESP32_Code

The code has been made based on the Arduino IDE to facilitate its use to the largest possible number of users

___

File contents:

* ## include.h
  - Main definitions and data structures
  ```c
  
  // Structure that contains the data required to interpretate the data received 
  // from DCS-Bios. It also points to the callback function
  struct actionReceived{
    uint16_t address; // DCS Bios Address assigned
    uint16_t mask;    // mask to be applied
    uint8_t shift;    // number of bits to be shifted
    void (*callback)(char *messageDCS, unsigned int, unsigned int, unsigned char); // function to execute. 
                      // Each function must decode and process the data present in the *messageDCS
  };
  
  -- Example:
     actionReceived T45_ActionsReceived[]={
       {0x9006,0x0010, 4,antiSkid_status},
       {0x902A,0x0003, 0,ILS_power_knob},
       {0x9024,0x8000,15,status_tacan_ON_OFF}
      };
  
  
  
  // Structure that contains the callback functions to execute after receiving the
  // corresponding address from DCS-Bios for each module
  struct moduleActionsReceived{
    uint16_t moduleId;  // Module Id present in the address.h file 
    uint8_t numActions; // Number of actions associated to this module
    struct actionReceived *actionSet; // Set of actions
  };
  
  -- Example:
     moduleActionsReceived moduleActionsReceived[]={
       // Module, Num_Actions, Set_of_Actions
       {A_4E_C,1,A4EC_ActionsReceived},
       {T_45  ,3,T45_ActionsReceived},
       {F_5E_3,3,F5E3_ActionsReceived}
     };
  
  
  
  // Structure that contains the set of commands to send for each module
  struct moduleActionsToDo{
    uint16_t moduleId;
    const char **actionSet;
  };
  
  -- Example:
     moduleActionsToDo moduleSetToDo[]={
       {A_4E_C,A4EC_ActionsToDo},
       {T_45, T45_ActionsToDo},
       {F_5E_3,F5E3_ActionsToDo}
     };
     
     where T45_ActionsToDo is somehing like this:
         const char *T45_ActionsToDo[]{
          // "_" means not implemented
          "_",            // Button 0 Dial TACAN 
          "_",            // Button 1 Dial TACAN
          "_",            // Button 2 TACAN X
          "_",            // Button 3 TACAN Y
          "TACAN_PW 1",   // Button 4 TACAN ON
          "TACAN_PW 0",   // Button 5 TACAN OFF
          "VOR_ILS_PW 1", // Button 6 ILS ON
          "VOR_ILS_PW 0", // Button 7 ILS OFF
          ....
         }  
     each array position identifies a button Id
  
  ```
  
* ### ESP32_Code.ino
  - LAN definitions
  - **ModuleActionsReceived** structure - It contains the required data/function for each module and for each DCSBios address.
  - **ModuleActionsToD** structure - It determines for each module the command set that must be sent to DCSBios from the button box.
  - UdP broadcast listener
  - **loop()** function that process the data received from DCSBios and to control if module has changed. In the loop the button box must be evaluated getting the button pressed and then sending the corresponding message.
  - **getButton()** - It is used to simulate a button box. It reads the integer present in the Serial port that corresponds to a button pressed.
  - **moduleExecutionButtonAction** - It search for the current module the corresponding command to send.
* ### MultiDCSBios.h
  - It contains the class that process the input stream from DCSBios. It is mainly based on the original [DCSBios](https://github.com/dcs-bios)
  - **executeAction()** receives the data read and its length (address / len). Determines the current module and launch the callback function.
* ### Module_Address.h
  - It contains the official module Id and also the module actions location in the array _moduleActionsReceived_ , thus 
* ### A4EC_functions.h / F5E3_functions.h / T45_functions.h
  - These files contains the defintions of the required callbacks to process the data from DCSBios and also the messages to send after pressing any button

----

> ___Comments:___ Functions defined for callbacks can be reused, just take into account the mask and shift parameters. It can be possible to add the *"**moduleId**"* as an additional parameter and then modulate the function behaviour.
