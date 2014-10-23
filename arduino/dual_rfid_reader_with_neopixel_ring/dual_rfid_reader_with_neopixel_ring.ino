#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>

const int Rfid1SpiSs = 10;
const int Rfid1SpiRst = 9;
const int Rfid2SpiSs = 8;
const int Rfid2SpiRst = 7;
const int RingData = 6;

String inputString = "";  
boolean stringComplete = false; 

MFRC522 rfid1(Rfid1SpiSs, Rfid1SpiRst);
MFRC522 rfid2(Rfid2SpiSs, Rfid2SpiRst);

Adafruit_NeoPixel ring = Adafruit_NeoPixel(24, RingData, NEO_GRB + NEO_KHZ800);
  
void setup() {  
  Serial.begin(9600);
  SPI.begin();
  ring.begin();
  ring.show();
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

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<ring.numPixels(); i++) {
      ring.setPixelColor(i, c);
      ring.show();
      delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< ring.numPixels(); i++) {
      ring.setPixelColor(i, Wheel(((i * 256 / ring.numPixels()) + j) & 255));
    }
    ring.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return ring.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return ring.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return ring.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}



void serialEvent() {  
  while (Serial.available()) {  
    char inChar = (char)Serial.read();  
    inputString += inChar;  
  
    if (inChar == '\n') {  
      stringComplete = true;  
    }  
  }  
  if(inputString == "light=OFF"){  
    colorWipe(ring.Color(0, 0, 0), 50);
  }  
  else if (inputString == "light=ON"){  
    colorWipe(ring.Color(255, 255, 255), 50); 
  }  
  else if (inputString == "light=DISCO"){  
    rainbowCycle(10);
  }
  inputString = "";  
  stringComplete = false;  
}  


