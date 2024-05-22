// / C++ code
//
#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>
// Define the pin connected to the DHT sensor
#define DHTPIN 8
// Define the type of DHT sensor (DHT11 or DHT22)
#define DHTTYPE DHT11 // Change to DHT22 if you are using a DHT22 sensor

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(1,2,4,5,6,7);
// const int tempPin = A0;
String ac, humidifier, condition;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Turn on the backlight
  pinMode(3, OUTPUT); // Assuming pin 10 is connected to backlight
  digitalWrite(3, HIGH); // Turn on backlight
  lcd.print("Start Detecting");
  dht.begin();
}


void loop() {
  // Read the humidity and temperature from the DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if any readings failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Good
  if(temperature < 30) {
    ac = "Off";
  } else {
    ac = "On";
  }

  if(humidity > 30 && humidity < 50) {
    humidifier = "Off"; 
  } else {
    humidifier = "On";
  }

  if (ac == "Off" && humidifier == "Off") {
    condition = "Good";
  } else if (ac == "On" && humidifier == "On") {
    condition = "Bad";
  } else {
    condition = "Warning";
  }

  // Clear the LCD and set the cursor
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Condition:");
  lcd.setCursor(0, 1);
  lcd.print(condition);
  delay(2000);
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("AC: ");
  lcd.print(ac);
  delay(2000);
  lcd.clear();
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("HMD: ");
  lcd.print(humidifier);
  delay(2000);
  lcd.clear();
  // Also print the temperature and humidity to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print(ac);
  Serial.println(" %");
  Serial.print(humidifier);
  Serial.println(" %");


  // Wait 2 seconds before updating again
}