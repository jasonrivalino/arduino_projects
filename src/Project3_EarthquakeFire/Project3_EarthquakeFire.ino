#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>

LiquidCrystal lcd(1,2,4,5,6,7);

#define smokePin A0

// Define pin connections for the sensors
const int tiltPin = 8;      // Tilt sensor connected to digital pin 2
const int vibrationPin = 9; // Vibration sensor connected to digital pin 3
const int buzzerPin = 10;
const int buttonPin = 11;
const int flamePin = 12;
const int maxSmoke = 170;
int flameVal = HIGH;
int smokeVal, tiltState, vibrationState;
int buttonState = 0; 
// DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
  // put your setup code here, to run once:
  // Turn on the backlight
  pinMode(3, OUTPUT); // Assuming pin 10 is connected to backlight
  digitalWrite(3, HIGH); // Turn on backlight

  // lcd.print("Earthquake");

  // Initialize the sensors
  pinMode(tiltPin, INPUT);
  pinMode(vibrationPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(smokePin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(flamePin, INPUT);
  // Start Serial Monitor for debugging
  // Serial.begin(9600);
}

void loop() {
  lcd.clear();
  // Read sensor values
  tiltState = digitalRead(tiltPin);
  vibrationState = digitalRead(vibrationPin);
  smokeVal = analogRead(smokePin);
  flameVal = digitalRead(flamePin);
  lcd.print("Tilt: ");
  lcd.print(tiltState);
  lcd.setCursor(0, 1);
  lcd.print("Geter: ");
  lcd.print(vibrationState);
  
  delay(500);
  lcd.clear();
  lcd.print("Smoke: ");
  lcd.print(smokeVal);
  lcd.setCursor(0, 1);
  lcd.print("Flame: ");
  lcd.print(flameVal);
  delay(500);

  // if (flameVal == LOW) {
  //   lcd.clear();
  //   lcd.print("PERTANDA API");
  //   delay(500);
  // } else {
  //   lcd.clear();
  //   lcd.print("TAKDE LA API");
  //   delay(500);
  // }

  // lcd.clear();
  // lcd.print("Flame: ");
  // lcd.print(flameVal);
  // delay(500);

  // // Display warning on LCD if any sensor is triggered
  // if (tiltState == HIGH || vibrationState == HIGH) {
  //   lcd.clear();
  //   lcd.print("Warning!");
  //   // lcd.setCursor(0, 1);
  //   // lcd.print("Earthquake");
  //   Serial.println("Earthquake Detected!");

  //   // Optional: Add buzzer or LED alert here
  //   // digitalWrite(buzzerPin, HIGH);
  //   // digitalWrite(ledPin, HIGH);
  // } else {
  //   lcd.clear();
  //   lcd.print("All is calm");
  //   Serial.println("No Earthquake.");
    
  //   // Optional: Turn off buzzer or LED alert here
  //   // digitalWrite(buzzerPin, LOW);
  //   // digitalWrite(ledPin, LOW);
  // }

  if ((tiltState == HIGH && vibrationState == HIGH) || smokeVal > maxSmoke || flameVal == LOW) {
    digitalWrite(buzzerPin, HIGH);
  }

  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    lcd.clear();
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  }
  delay(100); // Small delay to avoid flickering
}
