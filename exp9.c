#include <Adafruit_LiquidCrystal.h>
#include <EEPROM.h>
Adafruit_LiquidCrystal lcd(0);
const int tempPin = A0;
const int humPin = A2;
const int baroPin = A1;
const int buttonPins[] = {3, 4, 5, 6,9};
const int ledPins[] = {7, 8};
float temperature, humidity, pressure, dewPoint;
float minTemp = 100, maxTemp = -100;
float minHumidity = 100, maxHumidity = 0;
float minPressure = 1000, maxPressure = 0;
float tempAlertThreshold = 30.0;
float humAlertThreshold = 80.0;
float tempHistory[10] = {0};
float humHistory[10] = {0};
float pressHistory[10] = {0};
int historyIndex = 0;
int currentScreen = 0;
const int eepromStartAddr = 0;
int eepromIndex = 0;
float calculateDewPoint(float temp, float hum) {
 float a = 17.27;
 float b = 237.7;
 float alpha = ((a * temp) / (b + temp)) + log(hum / 100.0);
 return (b * alpha) / (a - alpha);
}
void logDataToEEPROM(float temp, float hum, float pres) {
 int addr = eepromStartAddr + eepromIndex * 12;
 if (addr + 12 > EEPROM.length()) eepromIndex = 0;
 EEPROM.put(addr, temp);
 EEPROM.put(addr + 4, hum);
  EEPROM.put(addr + 8, pres);
 eepromIndex++;
}
void readSensors() {
 temperature = analogRead(tempPin) * 5.0 / 1024.0 * 100.0;
 humidity = map(analogRead(humPin), 0, 1023, 0, 100);
 pressure = analogRead(baroPin) / 10.0;
 dewPoint = calculateDewPoint(temperature, humidity);
 if (temperature < minTemp) minTemp = temperature;
 if (temperature > maxTemp) maxTemp = temperature;
 if (humidity < minHumidity) minHumidity = humidity;
 if (humidity > maxHumidity) maxHumidity = humidity;
 if (pressure < minPressure) minPressure = pressure;
 if (pressure > maxPressure) maxPressure = pressure;
 tempHistory[historyIndex] = temperature;
 humHistory[historyIndex] = humidity;
 pressHistory[historyIndex] = pressure;
 historyIndex = (historyIndex + 1) % 10;
 logDataToEEPROM(temperature, humidity, pressure);
}
void checkAlerts() {
 if (temperature > tempAlertThreshold) {
 digitalWrite(ledPins[0], HIGH);
 } else {
 digitalWrite(ledPins[0], LOW);
 }
 if (humidity > humAlertThreshold) {
 digitalWrite(ledPins[1], HIGH);
 } else {
 digitalWrite(ledPins[1], LOW);
 }
}
void exportData() {
 Serial.println("Exporting data:");
 for (int i = 0; i < eepromIndex; i++) {
 int addr = eepromStartAddr + i * 12;
 float temp, hum, pres;
 EEPROM.get(addr, temp);
   EEPROM.get(addr + 4, hum);
 EEPROM.get(addr + 8, pres);
 Serial.print("T:");
 Serial.print(temp);
 Serial.print(" H:");
 Serial.print(hum);
 Serial.print(" P:");
 Serial.println(pres);
 }
}
void displayGraph() {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("T:");
 for (int i = 0; i < 10; i++) {
 lcd.print(tempHistory[i] > tempAlertThreshold ? "*" : ".");
 }
 lcd.setCursor(0, 1);
 lcd.print("H:");
 for (int i = 0; i < 10; i++) {
 lcd.print(humHistory[i] > humAlertThreshold ? "*" : ".");
 }
}
String forecast = "N/A";
void calculateWeatherForecast() {
 float pressureChange = pressHistory[9] - pressHistory[6];
 float humidity = humHistory[9];
 float temperature = tempHistory[9];
 if (pressureChange < -2.0 && humidity > 70) {
 forecast = "Rain expected";
 } else if (pressureChange > 2.0 && humidity < 50) {
 forecast = "Clear skies";
 } else if (temperature > 30.0) {
 forecast = "Hot weather";
 } else if (temperature < 5.0) {
 forecast = "Cold, frost";
 } else {
 forecast = "Stable";
 }
}
void displayForecast() {
 lcd.clear();
  lcd.setCursor(0, 0);
 lcd.print("Forecast:");
 lcd.setCursor(0, 1);
 lcd.print(forecast); }
void updateDisplay() {
 lcd.clear();
 if (currentScreen == 0) {
 lcd.setCursor(0, 0);
 lcd.print("T:");
 lcd.print(temperature);
 lcd.print("C H:");
 lcd.print(humidity);
 lcd.setCursor(0, 1);
 lcd.print("P:");
 lcd.print(pressure);
 lcd.print(" DP:");
 lcd.print(dewPoint);
 } else if (currentScreen == 1) {
 // Экстремумы
 lcd.setCursor(0, 0);
 lcd.print("Tmin:");
 lcd.print(minTemp);
 lcd.print(" Tmax:");
 lcd.print(maxTemp);
 lcd.setCursor(0, 1);
 lcd.print("Hmin:");
 lcd.print(minHumidity);
 lcd.print(" Hmax:");
 lcd.print(maxHumidity);
 } else if (currentScreen == 2) {
 displayGraph();
 } else if (currentScreen == 3) {
 exportData();
 lcd.setCursor(0, 0);
 lcd.print("Export Complete");

}
 else if (currentScreen == 4) {
 displayForecast();

}
}
void handleButtonPress() {
 for (int i = 0; i < 5; i++) {
 if (digitalRead(buttonPins[i]) == HIGH) {
   currentScreen = i;
 updateDisplay();
 delay(300);
 }
 }
}
void setup() {
 lcd.begin(16, 2);
 lcd.setBacklight(1);
 Serial.begin(9600);
 for (int i = 0; i < 4; i++) pinMode(buttonPins[i], INPUT_PULLUP);
 for (int i = 0; i < 2; i++) pinMode(ledPins[i], OUTPUT);
 lcd.setCursor(0, 0);
 lcd.print("Weather Station");
 delay(2000);
 lcd.clear();
}
void loop() {
 readSensors();
 checkAlerts();
 updateDisplay();
 handleButtonPress();
 calculateWeatherForecast();
 delay(2000);
}