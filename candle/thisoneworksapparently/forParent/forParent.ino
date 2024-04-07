#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>

#define RST_PIN2 8
#define SS_PIN2 7

#define RST_PIN 10
#define SS_PIN  9

#define STATE_STARTUP       0
#define STATE_STARTING      1
#define STATE_WAITING       2
#define STATE_SCAN_INVALID  3
#define STATE_SCAN_VALID    4
#define STATE_SCAN_MASTER   5
#define STATE_ADDED_CARD    6
#define STATE_REMOVED_CARD  7

#define REDPIN 7
#define GREENPIN 6
#define Relay 5

const int cardArrSize = 10;
const int cardSize    = 4;
int fsListener = analogRead(A0);
byte cardArr[cardArrSize][cardSize];
byte masterCard[cardSize] = {356,64,93,418};   //Change Master Card ID
byte readCard[cardSize];
byte readCard2[cardSize];

byte cardsStored = 0;

int fsT;
int fs1;
int fs2;
int fs3;
int fs4;
int fs5;

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522 mfrc522_2(SS_PIN2, RST_PIN2);

// Set the LCD I2C address

byte currentState = STATE_STARTUP;
unsigned long LastStateChangeTime;
unsigned long StateWaitTime;
//------------------------------------------------------------------------------------
int readCardState()
{
  int index;
  unsigned long reader1;
  unsigned long reader2;
  unsigned long reader3;
  unsigned long reader4;
  unsigned long reader5;

  // THIS IS READER 1. THIS IS READER 1. THIS IS READER 1. THIS IS READER 1. THIS IS READER 1. THIS IS READER 1. THIS IS READER 1. 

  Serial.print("Reader 1: ");
  for(index = 0; index < 4; index++)
  {
    readCard[index] = mfrc522.uid.uidByte[index];
    Serial.print(readCard[index]);
    if (index < 3)
    {
      Serial.print(",");
    }
  }

  reader1 = readCard[1];
  Serial.print(". The value of Reader 1 is ");
  Serial.print(reader1);
  
  if (reader1 == 14) {
    Serial.print(" - VALID. State: ");
    fs1 = 1;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  } else {
    Serial.print(" - INVALID. State: ");
    fs1 = 0;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  }

  Serial.println(" ");
  delay(10);

  // THIS IS READER 2. THIS IS READER 2. THIS IS READER 2. THIS IS READER 2. THIS IS READER 2. THIS IS READER 2. THIS IS READER 2. 

   Serial.print("Reader 2: ");
  for(index = 0; index < 4; index++)
  {
    readCard2[index] = mfrc522_2.uid.uidByte[index];
    Serial.print(readCard2[index]);
    if (index < 3)
    {
      Serial.print(",");
    }
  }

  reader2 = readCard2[1];
  Serial.print(". The value of Reader 2 is ");
  Serial.print(reader2);
  
  if (reader2 == 14) {
    Serial.print(" - VALID. State: ");
    fs2 = 1;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  } else {
    Serial.print(" - INVALID. State: ");
    fs2 = 0;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  }

  Serial.println(" ");
  delay(10);

  if (fsT == 2) {
    if (fsListener == 1) {
      Serial.print(" - Interrupt Recieved."); //whew...
      fs3 = 1;
      fs4 = 1;
      fs5 = 1;
      if (fsT = 5) {
        Serial.print(" Clear Condition Reached!");
      }
     }
  }else {
      fs3 = 0;
      fs4 = 0;
      fs5 = 0;
      Serial.print(" - Waiting for Interrupt..."); //whew...
  }

  Serial.println(" ");
  Serial.println("________________________");
  delay(1000);
}
void setup() 
{
  Serial.println("Active");
  SPI.begin();         // Init SPI Bus
  mfrc522.PCD_Init();
  delay(50);
  mfrc522_2.PCD_Init();
  delay(50);
 
  pinMode(2,INPUT);

  fsT = 0;
  fs1 = 0;
  fs2 = 0;
  fs3 = 0;
  fs4 = 0;
  fs5 = 0;
  fsListener = digitalRead(2);
  LastStateChangeTime = millis();
  
  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() 
{

  fsListener = digitalRead(2);

  if ((currentState != STATE_WAITING) &&
      (StateWaitTime > 0) &&
      (LastStateChangeTime + StateWaitTime < millis()))
  {
    readCardState();
  }

  // Look for new cards 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    readCardState(); 
  } 
  
  // Select one of the cards 

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  { 
    readCardState(); 
  }

  if ( ! mfrc522_2.PICC_IsNewCardPresent()) 
  { 
    readCardState(); 
  } 
  
  // Select one of the cards 

  if ( ! mfrc522_2.PICC_ReadCardSerial()) 
  { 
    readCardState(); 
  }
}



