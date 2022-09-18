#include <SPI.h>
#include <MFRC522.h>
 
#define SDA_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SDA_PIN, RST_PIN);   // Init MFRC522 module

// mfrc522.uid.uidByte is 10 byte. Cards and tags are usually 4 bytes so we use only that
const byte REGISTERED_CARD[10] = {0x00, 0x00, 0x00, 0x00};

// Compares 10 bytes from read card against our REGISTERED_CARD
bool check_access(byte rfid[10], byte card[10])
{
  for (byte i = 0; i < 10; i++)
  {
    if (rfid[i] != card[i])
    {
      return false;
    }
  }

  return true;
}

void setup() 
{
  Serial.begin(9600);   // Init a serial communication
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  Serial.println("Approximate your card to the reader...");
}

void loop() 
{
  // Do nothing if no card/tag is nearby
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() )
  {
    return;
  }

  if (check_access(mfrc522.uid.uidByte, REGISTERED_CARD))
  {
    Serial.println("Authorized access");
    delay(4000); // wait 4s before trying to read again
  }
  else
  {
    Serial.println("Access denied");
    delay(4000); // wait 4s before trying to read again
  }
}

