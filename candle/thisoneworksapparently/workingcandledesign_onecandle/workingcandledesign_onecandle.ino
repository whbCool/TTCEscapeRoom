#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>

#define RST_PIN2 10
#define SS_PIN2 9

#define RST_PIN 8
#define SS_PIN  7

#define RST_PIN3 6
#define SS_PIN3 5

#define RST_PIN4 4
#define SS_PIN4 3

#define RST_PIN5 2
#define SS_PIN5 1

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
byte cardArr[cardArrSize][cardSize];
byte masterCard[cardSize] = {356,64,93,418};   //Change Master Card ID
byte readCard[cardSize];
byte readCard2[cardSize];
byte readCard3[cardSize];
byte readCard4[cardSize];
byte readCard5[cardSize];
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
MFRC522 mfrc522_3(SS_PIN3, RST_PIN3);
MFRC522 mfrc522_4(SS_PIN4, RST_PIN4);
MFRC522 mfrc522_5(SS_PIN5, RST_PIN5);
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
  
  if (reader1 == 210) {
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
  
  if (reader2 == 173) {
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

// THIS IS READER 3. THIS IS READER 3. THIS IS READER 3. THIS IS READER 3. THIS IS READER 3. THIS IS READER 3. THIS IS READER 3. 

  Serial.print("Reader 3: ");
  for(index = 0; index < 4; index++)
  {
    readCard3[index] = mfrc522_3.uid.uidByte[index];
    Serial.print(readCard3[index]);
    if (index < 3)
    {
      Serial.print(",");
    }
  }

  reader3 = readCard3[1];
  Serial.print(". The value of Reader 3 is ");
  Serial.print(reader3);
  
  if (reader3 == 173) {
    Serial.print(" - VALID. State: ");
    fs3 = 1;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  } else {
    Serial.print(" - INVALID. State: ");
    fs3 = 0;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  }

  Serial.println(" ");
  delay(10);

  // THIS IS READER 4. THIS IS READER 4. THIS IS READER 4. THIS IS READER 4. THIS IS READER 4. THIS IS READER 4. THIS IS READER 4.  

  Serial.print("Reader 4: ");
  for(index = 0; index < 4; index++)
  {
    readCard4[index] = mfrc522_4.uid.uidByte[index];
    Serial.print(readCard4[index]);
    if (index < 3)
    {
      Serial.print(",");
    }
  }

  reader4 = readCard4[1];
  Serial.print(". The value of Reader 4 is ");
  Serial.print(reader4);
  
  if (reader4 == 173) {
    Serial.print(" - VALID. State: ");
    fs4 = 1;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  } else {
    Serial.print(" - INVALID. State: ");
    fs4 = 0;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  }

  Serial.println(" ");
  delay(10);

  // THIS IS READER 5. THIS IS READER 5. THIS IS READER 5. THIS IS READER 5. THIS IS READER 5. THIS IS READER 5. THIS IS READER 5. 

  Serial.print("Reader 5: ");
  for(index = 0; index < 4; index++)
  {
    readCard5[index] = mfrc522_5.uid.uidByte[index];
    Serial.print(readCard5[index]);
    if (index < 3)
    {
      Serial.print(",");
    }
  }

  reader5 = readCard5[1];
  Serial.print(". The value of Reader 5 is ");
  Serial.print(reader5);
  
  if (reader5 == 173) {
    Serial.print(" - VALID. State: ");
    fs5 = 1;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  } else {
    Serial.print(" - INVALID. State: ");
    fs5 = 0;
    fsT = fs1 + fs2 + fs3 + fs4 + fs5;
    Serial.print(fsT);
  }

  Serial.println(" ");
  delay(10);

  if (fsT == 5) {
    Serial.print(" - CLEAR CONDITION REACHED!"); //whew...
  }
}
void setup() 
{
  Serial.println("Active");
  SPI.begin();         // Init SPI Bus
  mfrc522.PCD_Init();
  delay(50);
  mfrc522_2.PCD_Init();
  delay(50);
  mfrc522_3.PCD_Init();
  delay(50);
  mfrc522_4.PCD_Init();
  delay(50);
  mfrc522_5.PCD_Init();
  delay(50);
  fsT = 0;
  fs1 = 0;
  fs2 = 0;
  fs3 = 0;
  fs4 = 0;
  fs5 = 0;
  LastStateChangeTime = millis();
  
  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() 
{

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

  if ( ! mfrc522_3.PICC_IsNewCardPresent()) 
  { 
    readCardState(); 
  } 
  
  // Select one of the cards 

  if ( ! mfrc522_3.PICC_ReadCardSerial()) 
  { 
    readCardState();
  }

  if ( ! mfrc522_4.PICC_IsNewCardPresent()) 
  { 
    readCardState(); 
  } 
  
  // Select one of the cards 

  if ( ! mfrc522_4.PICC_ReadCardSerial()) 
  { 
    readCardState(); 
  }

  if ( ! mfrc522_5.PICC_IsNewCardPresent()) 
  { 
    readCardState(); 
  } 
  
  // Select one of the cards 

  if ( ! mfrc522_5.PICC_ReadCardSerial()) 
  { 
    readCardState();
  }
}


