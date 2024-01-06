#include <SPI.h>
#include <TFT.h>
#include <MFRC522.h>


#define cs 10
#define dc 9
#define rst 8


#define RST_PIN 5
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN);

TFT TFTscren = TFT(cs, dc, rst);

const int fsrPin = A0;
const int buttonPin = 2;
const int ledPin = 6;
const int buzzer = 4;
const int pirPin = 7;


bool systemArmed = true;

bool alarm = false;

void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();
  TFTscren.begin();
  TFTscren.background(0, 0, 0);
  TFTscren.stroke(255, 255, 255);
  TFTscren.setTextSize(2);
  TFTscren.text("Sistem", 10, 15);
  TFTscren.text("activat!", 60, 30);

  pinMode(fsrPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pirPin, INPUT);
}

void loop() {
  // Verifică presiunea cu senzorul FSR
  int fsrValue = analogRead(fsrPin);
  boolean motionDetected = digitalRead(pirPin);
  Serial.print("Valoare FSR: ");
  Serial.println(fsrValue);

  
  if (systemArmed == true) {

    if (alarm == false) {
      TFTscren.background(0, 0, 0);
      TFTscren.stroke(255, 255, 255);
      TFTscren.line(0, 50, 160, 50);
      TFTscren.setTextSize(2);
      TFTscren.text("Sistem", 10, 15);
      TFTscren.text("activat!", 60, 30);
      delay(100);
    }


    if (motionDetected == true) {

      TFTscren.stroke(255, 0, 0);
      TFTscren.text("Miscare", 30, 70);
      TFTscren.text("detectata!", 20, 90);
      delay(250);

      for (int i = 0; i < 5; ++i) {
        digitalWrite(ledPin, HIGH);
        delay(150);  // Stare HIGH pentru 250 ms
        digitalWrite(ledPin, LOW);
        delay(150);  // Stare LOW pentru 250 ms
      }
    }

    if (rfid.PICC_IsNewCardPresent()) {
      // Dacă un card este prezent, îl citim
      Serial.println("Card detectat");
      if (rfid.PICC_ReadCardSerial()) {

        TFTscren.stroke(255, 0, 255);
        TFTscren.text("Se citeste", 10, 70);
        TFTscren.text("cardul...", 40, 90);
        delay(1000);

        String content = "";
        byte letter;
        for (byte i = 0; i < rfid.uid.size; i++) {
          Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(rfid.uid.uidByte[i], HEX);
          content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
          content.concat(String(rfid.uid.uidByte[i], HEX));
        }
        Serial.println();
        content.toUpperCase();

        if (alarm == true) {
          // Dezactivează alarma doar dacă sistemul este armat și alarma este activată
          if ((content.substring(1) == "40 99 2D 14")) {
            deactivateAlarm();
          } else {
            TFTscren.background(0, 0, 0);
            TFTscren.stroke(255, 0, 0);
            TFTscren.text("Card", 10, 50);
            TFTscren.text("invalid!!!", 10, 70);
            delay(1000);
          }
        }

        rfid.PICC_HaltA();
        delay(1000);
      }
    }

    if (fsrValue < 300 || alarm == true) {
      activateAlarm();
    }

    delay(200);
  }
}

void activateAlarm() {
  digitalWrite(ledPin, HIGH);
  tone(buzzer, 1050);
  alarm = true;

  TFTscren.background(0, 0, 0);
  TFTscren.stroke(0, 255, 0);
  TFTscren.setTextSize(2);
  TFTscren.text("ALERTA!", 40, 40);
  TFTscren.stroke(255, 255, 255);
  TFTscren.line(0, 65, 160, 65);
}

void deactivateAlarm() {
  digitalWrite(ledPin, LOW);
  noTone(buzzer);
  alarm = false;

  TFTscren.background(0, 0, 0);
  TFTscren.stroke(62, 255, 0);
  TFTscren.setTextSize(2);
  TFTscren.text("Alarma", 10, 35);
  TFTscren.text("dezactivata!", 30, 50);
  delay(1000);
}
