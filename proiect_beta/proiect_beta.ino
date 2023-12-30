//TO DO: mai am de legat keypad si de facut logica butonului si a keypadului, de incercat sa nu mai flicare ecranul, incerc sa fac ledul sa palpaie, de facut 8 fire din mama in tata pt keypad


#include <SPI.h>

#include <TFT.h>

#define cs 10
#define dc 9
#define rst 8

TFT TFTscren = TFT(cs, dc, rst);

const int fsrPin = A0;
const int buttonPin = 2;
const int ledPin = 6;
const int buzzer = 4;

const int numChars = 4;
char password[numChars] = { '1', '2', '3', '4' };
char enteredPassword[numChars];

boolean systemArmed = true;

bool alarm = false;

void setup() {
  Serial.begin(9600);
  TFTscren.begin();
  TFTscren.background(0, 0, 0);
  TFTscren.stroke(255, 255, 255);
  TFTscren.setTextSize(2);

  TFTscren.text("Sistem activat!", 10, 60);

  pinMode(fsrPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Verifică presiunea cu senzorul FSR
  int fsrValue = analogRead(fsrPin);
  Serial.print("Valoare FSR: ");
  Serial.println(fsrValue);
  if (systemArmed == true) {

    if (alarm == false) {
      TFTscren.background(0, 0, 0);
      TFTscren.stroke(255, 255, 255);
      TFTscren.setTextSize(2);
      TFTscren.text("Sistem activat!", 10, 60);
    }

    if (fsrValue < 300 || alarm==true) {
      activateAlarm();
    }

    // Verifică apăsarea butonului
    if (digitalRead(buttonPin) == HIGH) {
      deactivateAlarm();
    }
  }
  delay(200);
}

void activateAlarm() {
  digitalWrite(ledPin, HIGH);
  tone(buzzer, 1050);
  alarm = true;

  TFTscren.background(0, 0, 0);
  TFTscren.stroke(255, 255, 255);
  TFTscren.setTextSize(2);
  TFTscren.text("ALERTA!", 10, 60);

  for (int i = 0; i < 5; ++i) {
    digitalWrite(ledPin, HIGH);
    delay(250);  // Stare HIGH pentru 250 ms
    digitalWrite(ledPin, LOW);
    delay(250);  // Stare LOW pentru 250 ms
  }
}

void deactivateAlarm() {
  digitalWrite(ledPin, LOW);
  noTone(buzzer);
  alarm = false;

  TFTscren.background(0, 0, 0);
  TFTscren.stroke(255, 255, 255);
  TFTscren.setTextSize(2);
  TFTscren.text("Sistem Dezactivat!", 10, 60);
}
