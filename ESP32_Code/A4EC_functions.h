	/*
 * Main data structures
 */

// From DCSBios - declarations
void fuel_gauge(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);
void check_2(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift);

actionReceived A4EC_ActionsReceived[]={
    {0x840C,0xFFFF,0,fuel_gauge}
};

const char *A4EC_ActionsToDo[]{
  "TACAN_MODE INC", // 0 Dial TACAN REC-AA/TR ++
  "TACAN_MODE DEC", // 1 Dial TACAN REC-AA/TR --
  "TACAN_ANT_CONT 0", // 2 TACAN X
  "TACAN_ANT_CONT 1", // 3 TACAN Y
  "-", // 4 TACAN ON
  "-", // 5 TACAN OFF
  "-", // 6 ILS ON
  "-", // 7 ILS OFF
  "TACAN_CHAN_MAJ INC", // 8 TACAN H++
  "TACAN_CHAN_MAJ DEC", // 9 TACAN H --
  "TACAN_CHAN_MIN INC", // 10 TACAN L++
  "TACAN_CHAN_MIN DEC", // 11 TACAN L--
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
  "ARC51_FREQ_10MHZ INC", // 35 R1_0 ++ (Left to Right)
  "ARC51_FREQ_10MHZ DEC", // 36 R1_0 --
  "ARC51_FREQ_1MHZ INC", // 37 R1_1 ++
  "ARC51_FREQ_1MHZ DEC", // 38 R1_1 --
  "ARC51_FREQ_50KHZ INC", // 39 R1_2 ++
  "ARC51_FREQ_50KHZ DEC", // 40 R1_2 --
  "-", // 41 R1_3 ++
  "-", // 42 R1_3 ++
  "-", // 43 R1_4 ++
  "-", // 44 R1_4 --
  "ARC51_FREQ_PRE INC", // 45 R1 Channel ++
  "ARC51_FREQ_PRE DEC", // 46 R1 Channel --
  "ARC51_MODE DEC", // 47 R1_OFF-ADF --
  "ARC51_MODE INC", // 48 R1_OFF-ADF ++
  "ARC51_XMIT_MODE DEC", // 49 R1_MAN-GUARD --
  "ARC51_XMIT_MODE INC", // 50 R1_MAN-GUARD ++
  "-", // 51 R1 AM
  "-", // 52 R1 FM
  "-" // 53 R1 PRG
};



// From DCSBios

void fuel_gauge(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  uint16_t data = ((messageDCS[1] << 8 | messageDCS[0])& mask)>>shift;
  Serial.print("Fuel:");
  Serial.println(data);  
}
void check_2(char *messageDCS, unsigned int len, unsigned int mask, unsigned char shift){
  Serial.print("Received message:");
  Serial.print((messageDCS[1] << 8 | messageDCS[0])& mask);
  Serial.print(" with len: ");
  Serial.print(len);
  Serial.print(" - mask:");
  Serial.print(mask);
  Serial.print(" - shift:");
  Serial.print(shift);
}
