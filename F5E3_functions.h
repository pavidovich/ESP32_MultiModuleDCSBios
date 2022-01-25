/*
 * Main data structures
 */

// From DCSBios - declarations
void check_3(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);
void Right_Channel_Selector(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);
void Left_Channel_Selector(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);
void Tacan_Channel(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);

// Actions structure
actionReceived F5E3_ActionsReceived[]={
    {0x7714, 0,0,Tacan_Channel},
    {0x76fc,0x7800,11,Left_Channel_Selector},
    {0x76fe,0x0F00, 8,Right_Channel_Selector}
};

const char *F5E3_ActionsToDo[]{
  "TACAN_MODE INC", // 0 Dial TACAN REC-AA/TR ++
  "TACAN_MODE DEC", // 1 Dial TACAN REC-AA/TR --
  "TACAN_XY 1", // 2 TACAN X
  "TACAN_XY 0", // 3 TACAN Y
  "-", // 4 TACAN ON
  "-", // 5 TACAN OFF
  "-", // 6 ILS ON
  "-", // 7 ILS OFF
  "TACAN_10 INC", // 8 TACAN H++
  "TACAN_10 DEC", // 9 TACAN H --
  "TACAN_1 INC", // 10 TACAN L++
  "TACAN_1 DEC", // 11 TACAN L--
  "-", // 12 ILS H++
  "-", // 13 ILS H--
  "-", // 14 ILS L++
  "-", // 15 ILS L--
  "-", // 16 R2_0 ++ (Left to Right)
  "-", // 17 R2_0 --
  "-", // 18 R2_1 ++
  "-", // 19 R2_1 --
  "-", // 20 R2_2 ++
  "-", // 21 R2_2 --
  "-", // 22 R2_3 ++
  "-", // 23 R2_3 ++
  "-", // 24 R2_4 ++
  "-", // 25 R2_4 --
  "-", // 26 R2 Channel ++
  "-", // 27 R2 Channel --
  "-", // 28 R2_OFF-ADF --
  "-", // 28 R2_OFF-ADF ++
  "-", // 30 R2_MAN-GUARD --
  "-", // 31 R2_MAN-GUARD ++
  "-", // 32 R2 AM
  "-", // 33 R2 FM
  "-", // 34 R2 PRG
  "UHF_100MHZ_SEL INC", // 35 R1_0 ++ (Left to Right)
  "UHF_100MHZ_SEL DEC", // 36 R1_0 --
  "UHF_10MHZ_SEL INC", // 37 R1_1 ++
  "UHF_10MHZ_SEL DEC", // 38 R1_1 --
  "UHF_1MHZ_SEL INC", // 39 R1_2 ++
  "UHF_1MHZ_SEL DEC", // 40 R1_2 --
  "UHF_01MHZ_SEL INC", // 41 R1_3 ++
  "UHF_01MHZ_SEL DEC", // 42 R1_3 ++
  "UHF_0025MHZ_SEL INC", // 43 R1_4 ++
  "UHF_0025MHZ_SEL DEC", // 44 R1_4 --
  "UHF_PRESET_SEL INC", // 45 R1 Channel ++
  "UHF_PRESET_SEL DEC", // 46 R1 Channel --
  "UHF_FUNC DEC", // 47 R1_OFF-ADF --
  "UHF_FUNC INC", // 48 R1_OFF-ADF ++
  "UHF_FREQ DEC", // 49 R1_MAN-GUARD --
  "UHF_FREQ INC", // 50 R1_MAN-GUARD ++
  "-", // 51 R1 AM
  "-", // 52 R1 FM
  "UHF_PRE_SET 1" // 53 R1 PRG
};


// From DCSBios

void Right_Channel_Selector(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask)>>shift;
  Serial.print("TACAN Right channel:");
  Serial.println(data);
}

void Left_Channel_Selector(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask)>>shift;
  Serial.print("TACAN Left channel:");
  Serial.println(data);
}


void Tacan_Channel(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
 Serial.print("Tacan Channel:");
 messageDCS[4]=0; // It ensures the end of the string
 Serial.println(messageDCS);  
}
void check_3(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  Serial.print("Received message:");
  Serial.print((messageDCS[1] << 8 | messageDCS[0])& mask);
  Serial.print(" with len: ");
  Serial.print(len);
  Serial.print(" - mask:");
  Serial.print(mask);
  Serial.print(" - shift:");
  Serial.print(shift);
}
