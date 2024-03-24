#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define the analog pins for the MQ sensors
const int mq3SensorPin = A1;
const int mq4SensorPin = A2;

// Define the digital pin for the DHT11 sensor
const int dhtPin = 2;

// Create an instance of the DHT sensor
DHT dht(dhtPin, DHT11);

// Define LCD settings
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();         
  lcd.backlight();    

  // Display "Welcome" on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Welcome");

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Read the analog value from the MQ-3 alcohol sensor
  int mq3SensorValue = analogRead(mq3SensorPin);
  float mq3Voltage = mq3SensorValue * (5.0 / 1023.0);
  
  // Read the analog value from the MQ-4 methane sensor
  int mq4SensorValue = analogRead(mq4SensorPin);
  float mq4Voltage = mq4SensorValue * (5.0 / 1023.0);

  // Read temperature and humidity from the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Print the sensor values to the serial monitor
  Serial.print("MQ-3 Sensor - Value: ");
  Serial.print(mq3SensorValue);
  Serial.print(", Voltage: ");
  Serial.print(mq3Voltage);
  Serial.println("V");

  lcd.clear();

  Serial.print("MQ-4 Sensor - Value: ");
  Serial.print(mq4SensorValue);
  Serial.print(", Voltage: ");
  Serial.print(mq4Voltage);
  Serial.println("V");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Display sensor values on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Methane: ");
  lcd.print(mq4SensorValue);

  lcd.setCursor(0, 1);
  lcd.print("Alcohol: ");
  lcd.print(mq3SensorValue);

  delay(2000); // Adjust delay as needed
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print(" C");

  delay(2000); // Adjust delay as needed
}
