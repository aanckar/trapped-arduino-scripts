/*
 * RFID CARD READER
 * 
 * Reads RFID cards and does stuff as a consequence.
 *   
 * by Trapped Room Escape
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 3
// Create MFRC522 instance.
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int LED = 13;
// Vitt kort
const unsigned long CARD1 = 4294945317;
// Blå nyckelring
const unsigned long CARD2 = 4294963849;

const unsigned long CARDS[2] = {
  4294945317, // Vitt kort
  4294963849  // Blå nyckelring
};
const int CARDS_LENGTH = sizeof(CARDS)/sizeof(CARDS[0]);

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("Scan PICC to see UID and type...");
}

void loop() {
  // Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card. PICC_HaltA() is automatically called.
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  // Read card UID
  unsigned long uid = readCard();

  // Check if card UID is accepted
  int i;
  for ( i=0; i<CARDS_LENGTH; i++ ) {
    if ( uid == CARDS[i] ) {
      cardCorrect();
    }
  }
}

unsigned long readCard() {
  unsigned long uid;
  uid =  mfrc522.uid.uidByte[0] << 24;
  uid += mfrc522.uid.uidByte[1] << 16;
  uid += mfrc522.uid.uidByte[2] <<  8;
  uid += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  Serial.println(uid);
  return uid;
}

void cardCorrect() {
  Serial.println("Card recognized");
  digitalWrite(LED, HIGH);
  delay(1500);
  digitalWrite(LED, LOW);
}
