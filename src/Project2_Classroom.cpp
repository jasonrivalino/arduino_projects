#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>

// Define the pin connected to the DHT sensor
#define DHTPIN 8
#define MOTIONPIN 9
#define BUTTONPIN 10

// Define the type of DHT sensor (DHT11 or DHT22)
#define DHTTYPE DHT11 // Change to DHT22 if you are using a DHT22 sensor

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 13, 4, 5, 6, 7);

int motionState, buttonState;
float temp;
String delayInput, intervalInput;

void setup() {
  lcd.begin(16, 2);

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  // pinMode(13, OUTPUT);
  pinMode(MOTIONPIN, INPUT);
  pinMode(BUTTONPIN, INPUT_PULLUP);
  dht.begin();
  delayInput = "7000";
  intervalInput = "100";
  Serial.begin(9600);
  // Serial.println("System ready.");
}

void loop() {
  scan();
  
  int curInt = 0;
  while (curInt < delayInput.toInt()) {
    buttonState = digitalRead(BUTTONPIN);
    if (buttonState == LOW) {
      scan();
    }
    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      command.trim();
      if (command == "scan") {
        scan();
      }
      if (command == "delay") {
        while (!Serial.available()) {
          delay(1);
        }
        delayInput = Serial.readStringUntil('\n');
        delayInput.trim();
      }
      if (command == "interval") {
        while (!Serial.available()) {
          delay(1);
        }
        intervalInput = Serial.readStringUntil('\n');
        intervalInput.trim();
      }
    }
    else {
      delay(100);
      curInt += 100;
    }
  }
  
}

void scan() {
  lcd.clear();
  Serial.println("Scan triggered");
  motionState = digitalRead(MOTIONPIN);
  temp = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("RUANG: ");
  if (motionState == HIGH) {
    lcd.print("BERISI");
  } else {
    lcd.print("KOSONG");
  }

  lcd.setCursor(0, 1);
  
  lcd.print("LAMPU: ");
  if (motionState == HIGH) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  } 
  delay(2000);
  lcd.clear();
  // lcd.setCursor(0, 1);
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("KIPAS: ");
  if (temp > 30 && motionState == HIGH) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }

  delay(intervalInput.toInt());

}
