#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN5 10
#define RST_PIN5 9
#define SS_PIN1 1
#define RST_PIN1 2
#define SS_PIN2 3
#define RST_PIN2 4
#define SS_PIN3 5
#define RST_PIN3 6
#define SS_PIN4 7
#define RST_PIN4 8

MFRC522 mfrc522_1(SS_PIN1, RST_PIN1);
MFRC522 mfrc522_2(SS_PIN2, RST_PIN2);
MFRC522 mfrc522_3(SS_PIN3, RST_PIN3);
MFRC522 mfrc522_4(SS_PIN4, RST_PIN4);
MFRC522 mfrc522_5(SS_PIN5, RST_PIN5);

// tag 1: F3 E7 9F 0D
// tag 2: 53 0E A2 0D
// tag 3: D3 AD FE F6
// tag 4: 33 7E 84 0D
// tag 5: 23 23 FB 0D
int state = 0; //Defines the state of the puzzle. Value goes up by one when candle is placed
int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;
void setup() {
  Serial.begin(9600); // This is my clock and will align the timing
  SPI.begin(); // starts SPI
  mfrc522_1.PCD_Init(); //starts RFID reader
  delay(10);
  mfrc522_2.PCD_Init();
  delay(10);
  mfrc522_3.PCD_Init();
  delay(10);
  mfrc522_4.PCD_Init();
  delay(10);
  mfrc522_5.PCD_Init();
  delay(10); // delay for RFID to setup
  Serial.println("Readers ready!");
}

void loop() {

// idle active state
if ( ! mfrc522_1.PICC_IsNewCardPresent()) {
		return;
	}

if ( ! mfrc522_2.PICC_IsNewCardPresent()) {
		return;
	}

if ( ! mfrc522_3.PICC_IsNewCardPresent()) {
		return;
	}

if ( ! mfrc522_4.PICC_IsNewCardPresent()) {
		return;
	}

if ( ! mfrc522_5.PICC_IsNewCardPresent()) {
		return;
	}

// we need one of the uids here 
	if ( ! mfrc522_1.PICC_ReadCardSerial()) {
		return;
	}

  if ( ! mfrc522_2.PICC_ReadCardSerial()) {
		return;
	}

  if ( ! mfrc522_3.PICC_ReadCardSerial()) {
		return;
	}

  if ( ! mfrc522_4.PICC_ReadCardSerial()) {
		return;
	}

  if ( ! mfrc522_5.PICC_ReadCardSerial()) {
		return;
	}

  Serial.print("UID Tag 1: ");
  String content1 = "";
  byte letter1;
  for (byte i = 0; i < mfrc522_1.uid.size; i++) {
    Serial.print(mfrc522_1.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522_1.uid.uidByte[i], HEX);
    content1.concat(String(mfrc522_1.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content1.concat(String(mfrc522_1.uid.uidByte[i], HEX));
  }
  Serial.println();
  content1.toUpperCase();

  Serial.print("UID Tag 2: ");
  String content2 = "";
  byte letter2;
  for (byte i = 0; i < mfrc522_2.uid.size; i++) {
    Serial.print(mfrc522_2.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522_2.uid.uidByte[i], HEX);
    content2.concat(String(mfrc522_2.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content2.concat(String(mfrc522_2.uid.uidByte[i], HEX));
  }
  Serial.println();
  content2.toUpperCase();

  Serial.print("UID Tag 3: ");
  String content3 = "";
  byte letter3;
  for (byte i = 0; i < mfrc522_3.uid.size; i++) {
    Serial.print(mfrc522_3.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522_3.uid.uidByte[i], HEX);
    content3.concat(String(mfrc522_3.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content3.concat(String(mfrc522_3.uid.uidByte[i], HEX));
  }
  Serial.println();
  content3.toUpperCase();

  Serial.print("UID Tag 4: ");
  String content4 = "";
  byte letter4;
  for (byte i = 0; i < mfrc522_4.uid.size; i++) {
    Serial.print(mfrc522_4.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522_4.uid.uidByte[i], HEX);
    content4.concat(String(mfrc522_4.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content4.concat(String(mfrc522_4.uid.uidByte[i], HEX));
  }
  Serial.println();
  content4.toUpperCase();

  Serial.print("UID Tag 5: ");
  String content5 = "";
  byte letter5;
  for (byte i = 0; i < mfrc522_5.uid.size; i++) {
    Serial.print(mfrc522_5.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522_5.uid.uidByte[i], HEX);
    content5.concat(String(mfrc522_5.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content5.concat(String(mfrc522_5.uid.uidByte[i], HEX));
  }
  Serial.println();
  content5.toUpperCase();

  if (content1.substring(1) == "F3 E7 9F 0D") {
    Serial.println("Correct key!");
    delay(1000);
    state = state + 1;
    state1 = 1;
  }

  if (content2.substring(1) == "53 0E A2 0D") {
    Serial.println("Correct key!");
    delay(1000);
    state = state + 1;
    state2 = 1;
  }

  if (content3.substring(1) == "D3 AD FE F6") {
    Serial.println("Correct key!");
    delay(1000);
    state = state + 1;
    state3 = 1;
  }

  if (content4.substring(1) == "33 7E 87 0D") {
    Serial.println("Correct key!");
    delay(1000);
    state = state + 1;
    state4 = 1;
  }

  if (content5.substring(1) == "23 23 FB 0D") {
    Serial.println("Correct key!");
    delay(1000);
    state = state + 1;
    state5 = 1;
  }
}

