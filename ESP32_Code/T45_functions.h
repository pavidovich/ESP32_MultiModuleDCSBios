<<<<<<< HEAD
/*
 * Main data structures
 */


// From DCSBios - Functionns declarations
void status_tacan_ON_OFF(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);
void antiSkid_status(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);
void ILS_power_knob(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);

// Actions structure
actionReceived T45_ActionsReceived[]={
    {0x9006,0x0010, 4,antiSkid_status},
    {0x902A,0x0003, 0,ILS_power_knob},
    {0x9024,0x8000,15,status_tacan_ON_OFF}
};


// To DCSBios - Messages

const char *T45_ActionsToDo[]{
  // "_" means not implemented

  "_", // 0 Dial Mode TACAN ++
  "_", // 1 Dial Mode TACAN --
  "_", // 2 TACAN X
  "_", // 3 TACAN Y
  "TACAN_PW 1", // 4 TACAN ON
  "TACAN_PW 0", // 5 TACAN OFF
  "VOR_ILS_PW 0", // 6 ILS OFF
  "VOR_ILS_PW 1", // 7 ILS ON
  "TACAN_CHAN_10 INC", // 8 TACAN H++
  "TACAN_CHAN_10 DEC", // 9 TACAN H --
  "TACAN_CHAN_1 INC", // 10 TACAN L++
  "TACAN_CHAN_1 DEC", // 11 TACAN L--
  "VOR_ILS_FREQ_1 INC", // 12 ILS H++
  "VOR_ILS_FREQ_1 DEC", // 13 ILS H--
  "VOR_ILS_FREQ_50 INC", // 14 ILS L++
  "VOR_ILS_FREQ_50 DEC", // 15 ILS L--
  "COMM_2_FREQ_010 DEC", // 16 R2_3 --
  "COMM_2_FREQ_010 INC", // 17 R2_3 ++
  "COMM_2_FREQ_1 INC", // 18 R2_2 ++
  "COMM_2_FREQ_1 DEC", // 19 R2_2 --
  "COMM_2_FREQ_10 INC", // 20 R2_1 ++
  "COMM_2_FREQ_10 DEC", // 21  R2_1 --
  "COMM_2_FREQ_100 INC", // 22 R2_0 ++ (Left to Right)
  "COMM_2_FREQ_100 DEC", // 23 R2_0 --
  "_", // 24 R2_4 ++
  "_", // 25 R2_4 --
  "_", // 26 R2 Channel ++
  "_", // 27 R2 Channel --
  "COMM_2_MODE DEC", // 28 R2_OFF-ADF --
  "COMM_2_MODE INC", // 29 R2_OFF-ADF ++
  "_", // 30 R2_MAN-GUARD -- 
  "_", // 31 R2_MAN-GUARD ++ 
  "COMM_2_AMFM 1", // 32 R2 AM
  "COMM_2_AMFM 0", // 33 R2 FM
  "_", // 34 R2 PRG
  "COMM_1_FREQ_010 INC", // 35 R1_0 ++ (Left to Right)
  "COMM_1_FREQ_010 DEC", // 36 R1_0 --
  "COMM_1_FREQ_1 INC", // 37 R1_1 ++
  "COMM_1_FREQ_1 DEC", // 38 R1_1 --
  "COMM_1_FREQ_10 INC", // 39 R1_2 ++
  "COMM_1_FREQ_10 DEC", // 40 R1_2 --
  "COMM_1_FREQ_100 DEC", // 41 R1_3 ++
  "COMM_1_FREQ_100 INC", // 42 R1_3 ++
  "_", // 43 R1_4 ++
  "_", // 44 R1_4 --
  "_", // 45 R1 Channel ++
  "_", // 46 R1 Channel --
  "COMM_1_MODE DEC", // 47 R1_OFF-ADF --
  "COMM_1_MODE INC", // 48 R1_OFF-ADF ++
  "_", // 49 R1_MAN-GUARD --
  "_", // 50 R1_MAN-GUARD ++
  "COMM_1_AMFM 1", // 51 R1 AM
  "COMM_1_AMFM 0", // 52 R1 FM
  "_" // 53 R1 PRG
};


// From DCSBios - Actions to do

void antiSkid_status(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask);
  if (data) {
   Serial.println("AntiSkid ON");
  } else {
     Serial.println("AntiSkid OFF");
    }
}

void status_tacan_ON_OFF(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask);
  if (data) {
   Serial.println("TACAN ON");
  } else {
     Serial.println("TACAN OFF");
    }
}

void ILS_power_knob(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask);
  switch(data){
    case 0:
      Serial.println("ILS OFF");
      break;
    case 1:
      Serial.println("ILS ON");
      break;
    case 2:
      Serial.println("ILS Test");
  }   
}
=======
/*
 * Main data structures
 */


// From DCSBios - Functionns declarations
void status_tacan_ON_OFF(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);
void antiSkid_status(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);
void ILS_power_knob(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);

// Actions structure
actionReceived T45_ActionsReceived[]={
    {0x9006,0x0010, 4,antiSkid_status},
    {0x902A,0x0003, 0,ILS_power_knob},
    {0x9024,0x8000,15,status_tacan_ON_OFF}
};


// To DCSBios - Messages

const char *T45_ActionsToDo[]{
  // "_" means not implemented

  "_", // 0 Dial Mode TACAN ++
  "_", // 1 Dial Mode TACAN --
  "_", // 2 TACAN X
  "_", // 3 TACAN Y
  "TACAN_PW 1", // 4 TACAN ON
  "TACAN_PW 0", // 5 TACAN OFF
  "VOR_ILS_PW 0", // 6 ILS ON
  "VOR_ILS_PW 1", // 7 ILS OFF
  
  "TACAN_CHAN_10 INC", // 8 TACAN H++
  "TACAN_CHAN_10 DEC", // 9 TACAN H --
  "TACAN_CHAN_1 INC", // 10 TACAN L++
  "TACAN_CHAN_1 DEC", // 11 TACAN L--
  
  "VOR_ILS_FREQ_1 INC", // 12 ILS H++
  "VOR_ILS_FREQ_1 DEC", // 13 ILS H--
  "VOR_ILS_FREQ_50 INC", // 14 ILS L++
  "VOR_ILS_FREQ_50 DEC", // 15 ILS L--
  
  "COMM_2_FREQ_10 2\nCOMM_2_FREQ_10 1", // 16 R2_0 ++
  "COMM_2_FREQ_10 0\nCOMM_2_FREQ_10 1", // 17 R2_0 --
  "COMM_2_FREQ_1 2\nCOMM_2_FREQ_1 1", // 18 R2_1 ++
  "COMM_2_FREQ_1 0\nCOMM_2_FREQ_1 1", // 19 R2_1 --  
  "COMM_2_FREQ_010 2\nCOMM_2_FREQ_010 1", // 20 R2_2 ++ (Left to Right)
  "COMM_2_FREQ_010 0\nCOMM_2_FREQ_010 1", // 21 R2_2 --
  "COMM_2_FREQ_100 2\nCOMM_2_FREQ_100 1", // 22 R2_3 ++
  "COMM_2_FREQ_100 0\nCOMM_2_FREQ_100 1", // 23 R2_3 ++
  
  "COMM_2_FREQ_100 2\nCOMM_2_FREQ_100 1", // 24 R2_4 ++
  "COMM_2_FREQ_100 0\nCOMM_2_FREQ_100 1", // 25 R2_4 --
  "_", // 26 R2 Channel ++
  "_", // 27 R2 Channel --
  "COMM_2_MODE DEC", // 28 R2_OFF-ADF --
  "COMM_2_MODE INC", // 29 R2_OFF-ADF ++
  "_", // 30 R2_MAN-GUARD -- 
  "_", // 31 R2_MAN-GUARD ++ 
  "COMM_2_AMFM 1", // 32 R2 AM
  "COMM_2_AMFM 0", // 33 R2 FM
  "_", // 34 R2 PRG
  
  "COMM_1_FREQ_10 2\nCOMM_1_FREQ_10 1", // 35 R1_0 ++
  "COMM_1_FREQ_10 0\nCOMM_1_FREQ_10 1", // 36 R1_0 --
  "COMM_1_FREQ_1 2\nCOMM_1_FREQ_1 1", // 37 R1_1 ++
  "COMM_1_FREQ_1 0\nCOMM_1_FREQ_1 1", // 38 R1_1 --  
  "COMM_1_FREQ_010 2\nCOMM_1_FREQ_010 1", // 39 R1_2 ++ (Left to Right)
  "COMM_1_FREQ_010 0\nCOMM_1_FREQ_010 1", // 40 R1_2 --
  "COMM_1_FREQ_100 2\nCOMM_1_FREQ_100 1", // 41 R1_3 ++
  "COMM_1_FREQ_100 0\nCOMM_1_FREQ_100 1", // 42 R1_3 ++
  
  "COMM_1_FREQ_100 2\nCOMM_1_FREQ_100 1", // 43 R1_4 ++
  "COMM_1_FREQ_100 0\nCOMM_1_FREQ_100 1", // 44 R1_4 --
  "_", // 45 R1 Channel ++
  "_", // 46 R1 Channel --
  "COMM_1_MODE DEC", // 47 R1_OFF-ADF --
  "COMM_1_MODE INC", // 48 R1_OFF-ADF ++
  "_", // 49 R1_MAN-GUARD --
  "_", // 50 R1_MAN-GUARD ++
  "COMM_1_AMFM 1", // 51 R1 AM
  "COMM_1_AMFM 0", // 52 R1 FM
  "_" // 53 R1 PRG
};


// From DCSBios - Actions to do

void antiSkid_status(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask);
  if (data) {
   Serial.println("AntiSkid ON");
  } else {
     Serial.println("AntiSkid OFF");
    }
}

void status_tacan_ON_OFF(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask);
  if (data) {
   Serial.println("TACAN ON");
  } else {
     Serial.println("TACAN OFF");
    }
}

void ILS_power_knob(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask);
  switch(data){
    case 0:
      Serial.println("ILS OFF");
      break;
    case 1:
      Serial.println("ILS ON");
      break;
    case 2:
      Serial.println("ILS Test");
  }   
}
>>>>>>> 284416a61bb93ce7bed5c67dd5b1a8c8c24bdd38
