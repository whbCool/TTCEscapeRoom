#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>

// data pins are 5, 6, 7, 8, and 10. reset is 9. clock is 13. MISO is 11, MOSI is 12
// the idea is to leave SS_PIN alone, to comb the document for its use. somehow tihs code bypasses the firmware error.
// just need to rewire this to take five guys all at once...

// also, will made this :) anything using capital letters is the original author of this code, lol

#define RST_PIN 9
#define SS_PIN  5
#define SS_PIN_2 6
#define SS_PIN_3 7
#define SS_PIN_4 8
#define SS_PIN_5 10

// dont care about these. wish i bought a mega.

#define STATE_STARTUP       0
#define STATE_STARTING      1
#define STATE_WAITING       2
#define STATE_SCAN_INVALID  3
#define STATE_SCAN_VALID    4
#define STATE_SCAN_MASTER   0
#define STATE_ADDED_CARD    0
#define STATE_REMOVED_CARD  0

// or this. 

#define REDPIN 87
#define GREENPIN 86
#define Relay 85

int state = 0;

// cardArrSize shows how big the values are for the UID. interesting

const int cardArrSize = 9;
const int cardArrSize2 = 10;
const int cardArrSize3 = 11;
const int cardArrSize4 = 12;
const int cardSize = 4;
byte cardArr[cardArrSize2][cardSize];
byte cardArr2[cardArrSize3][cardSize];
byte cardArr3[cardArrSize][cardSize];
byte cardArr4[cardArrSize][cardSize];
byte cardArr5[cardArrSize4][cardSize];
byte masterCard[cardSize] = {111,210,73,72};   //Change Master Card ID

// looks like masterCard is the big player over here. gonnam make 4 more of these. need to read the RFIDs. thank god this already reads without the firmware. fuck firmware.


// oh god, the array sizes are different...

byte masterCard2[cardSize] = {243,231,159,13};
byte masterCard3[cardSize] = {35,35,251,13};
byte masterCard4[cardSize] = {83,14,162,13};
byte masterCard5[cardSize] = {211,173,254,246};

byte readCard[cardSize];
byte readCard2[cardSize];
byte readCard3[cardSize];
byte readCard4[cardSize];
byte readCard5[cardSize];
byte cardsStored = 5;

// Create MFRC522 instance

MFRC522 mfrc522(SS_PIN, RST_PIN);

// might have to create multiple instances of this also, since it calls out SS_PIN directly.

MFRC522 mfrc522_2(SS_PIN_2, RST_PIN);
MFRC522 mfrc522_3(SS_PIN_3, RST_PIN);
MFRC522 mfrc522_4(SS_PIN_4, RST_PIN);
MFRC522 mfrc522_5(SS_PIN_5, RST_PIN);

// yup, thats exactly what i had to do

// Set the LCD I2C address

byte currentState = STATE_STARTUP;
unsigned long LastStateChangeTime;
unsigned long StateWaitTime;

//------------------------------------------------------------------------------------
int readCardState()
{
  int index;
  Serial.print("Card Data - ");
  for(index = 0; index < 5; index++)
  {
    readCard[index] = mfrc522.uid.uidByte[index];

    // ok i thought this was nothing, turns out this was definitely something

    readCard2[index] = mfrc522_2.uid.uidByte[index];
    readCard3[index] = mfrc522_3.uid.uidByte[index];
    readCard4[index] = mfrc522_4.uid.uidByte[index];
    readCard5[index] = mfrc522_5.uid.uidByte[index];
    
    Serial.print(readCard[index]);
    Serial.print(readCard2[index]);
    Serial.print(readCard3[index]);
    Serial.print(readCard4[index]);
    Serial.print(readCard5[index]);
    
    if (index < 3)
    {
      Serial.print(",");
    }
  }
  Serial.println(" ");

  //Check Master Card

  // now this seems like a job for multiple masterCards. these lines below seem like callibration before rolling off. dont like that. the values will be preset beforehand. maybe i make a blank so any foreign objects get sent to a dummy value? american immigration, am i right? 
  if ((memcmp(readCard, masterCard, 4)) == 0)
  {
    return STATE_SCAN_MASTER;
  }

  if (cardsStored == 0)
  {
    return STATE_SCAN_INVALID;
  }

  for(index = 0; index < cardsStored; index++)
  {
    if ((memcmp(readCard, cardArr[index], 4)) == 0)
    {
      return STATE_SCAN_VALID;
    }
  }

  // aahhh, lines 104 to 110 show a valid case, showing cardArr as a checkpoint for validation. interesting. i need to tie this to an int for a counting design. " state " is the variable

 return STATE_SCAN_INVALID;
}

//------------------------------------------------------------------------------------
void addReadCard()
{
  int cardIndex;
  int index;

  if (cardsStored <= 20)
  {
    cardsStored++;
    cardIndex = cardsStored;
    cardIndex--;
  }

  for(index = 0; index < 4; index++)
  {
    cardArr[cardIndex][index] = readCard[index];
  }
}

//------------------------------------------------------------------------------------
void removeReadCard() 
{     
  int cardIndex;
  int index;
  boolean found = false;
  
  for(cardIndex = 0; cardIndex < cardsStored; cardIndex++)
  {
    if (found == true)
    {
      for(index = 0; index < 4; index++)
      {
        cardArr[cardIndex-1][index] = cardArr[cardIndex][index];
        cardArr[cardIndex][index] = 0;
      }
    }
    
    if ((memcmp(readCard, cardArr[cardIndex], 4)) == 0)
    {
      found = true;
    }
  }

  if (found == true)
  {
    cardsStored--;
  }
}

//------------------------------------------------------------------------------------
void updateState(byte aState)
{
  if (aState == currentState)
  {
    return;
  }

  // do state change
  switch (aState)
  {
    case STATE_STARTING:
      StateWaitTime = 1000;
      digitalWrite(REDPIN, HIGH);
      digitalWrite(GREENPIN, LOW);
      break;
    case STATE_WAITING:
      StateWaitTime = 0;
      digitalWrite(REDPIN, LOW);
      digitalWrite(GREENPIN, LOW);
      break;
    case STATE_SCAN_INVALID:
      if (currentState == STATE_SCAN_MASTER)
      {
        addReadCard();
        aState = STATE_ADDED_CARD;
        StateWaitTime = 2000;
        digitalWrite(REDPIN, LOW);
        digitalWrite(GREENPIN, HIGH);
      }
      else if (currentState == STATE_REMOVED_CARD)
      {
        return;
      }
      else
      {
        StateWaitTime = 2000;
        digitalWrite(REDPIN, HIGH);
        digitalWrite(GREENPIN, LOW);
      }
      break;
    case STATE_SCAN_VALID:
      if (currentState == STATE_SCAN_MASTER)
      {
        removeReadCard();
        aState = STATE_REMOVED_CARD;
        StateWaitTime = 2000;
        digitalWrite(REDPIN, LOW);
        digitalWrite(GREENPIN, HIGH);
      }
      else if (currentState == STATE_ADDED_CARD)
      {
        return;
      }
      else
      {
        StateWaitTime = 2000;
        digitalWrite(REDPIN, LOW);
        digitalWrite(GREENPIN, HIGH);
        digitalWrite(Relay,LOW);
        delay(3000);
        digitalWrite(Relay,HIGH);
      }
      break;
    case STATE_SCAN_MASTER:
      StateWaitTime = 3000;
      digitalWrite(REDPIN, LOW);
      digitalWrite(GREENPIN, HIGH);
      break;
  }

  currentState = aState;
  LastStateChangeTime = millis();
}

void setup() 
{
  Serial.println("im starting");
  SPI.begin();         // Init SPI Bus
  mfrc522.PCD_Init();  // Init MFRC522

// a great wizard once told me that if i give this PDC_Init a 50 millisecond delay, i can cure world hunger and gain infinite riches. that dude was a weirdo, but it couldn't hurt, right?

  delay(50);

// there... i am still broke... and now hungry...

  LastStateChangeTime = millis();
  updateState(STATE_STARTING);

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay,HIGH);

  Serial.begin(9600);
  Serial.println("finished setup");
}

void loop() 
{
  byte cardState;

  // Look for new cards 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return; 
  } 
  
  // Select one of the cards 
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  { 
    return; 
  }
  
  Serial.println(readCardState());

  cardState = readCardState();
  updateState(cardState);
}