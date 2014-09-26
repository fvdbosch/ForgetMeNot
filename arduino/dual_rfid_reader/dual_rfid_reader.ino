#include <SPI.h>
#include <MFRC522.h>

const int Rfid1SpiSs = 10;
const int Rfid1SpiRst = 9;
const int Rfid2SpiSs = 8;
const int Rfid2SpiRst = 7;

MFRC522 rfid1(Rfid1SpiSs, Rfid1SpiRst);
MFRC522 rfid2(Rfid2SpiSs, Rfid2SpiRst);
  
void setup() {  
  Serial.begin(9600);
  SPI.begin();
}  
  
void loop() {
  checkRfid1();
  checkRfid2();
  
  delay(1000);
}  

void checkRfid1() {
  rfid1.PCD_Init();
  Serial.print("-B1-RFID1:");
  
  if (rfid1.PICC_IsNewCardPresent() && rfid1.PICC_ReadCardSerial()) {
    for (byte i = 0; i < rfid1.uid.size; i++) {
      Serial.print(rfid1.uid.uidByte[i] < 0x10 ? "0" : "");
      Serial.print(rfid1.uid.uidByte[i], HEX);
     } 
  } else {
    Serial.print("00000000");
  }
  
  Serial.print("-E1-");
}

void checkRfid2() {
  rfid2.PCD_Init();
  Serial.print("-B2-RFID2:");
  
  if (rfid2.PICC_IsNewCardPresent() && rfid2.PICC_ReadCardSerial()) {
    for (byte i = 0; i < rfid2.uid.size; i++) {
      Serial.print(rfid2.uid.uidByte[i] < 0x10 ? "0" : "");
      Serial.print(rfid2.uid.uidByte[i], HEX);
     } 

  } else {
    Serial.print("00000000");
  }
  
  Serial.println("-E2-");
}
