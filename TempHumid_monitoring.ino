#define BLYNK_TEMPLATE_ID "Your template ID" // Template ID
#define BLYNK_TEMPLATE_NAME "Temperature and humidity sensor" // Template name
#define BLYNK_AUTH_TOKEN "Your blynk token" // Blynk token

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> // ESP8266
#include <BlynkSimpleEsp8266.h> //Blink Lib
#include "DHT.h" // DHT lib

char auth[] = "Your Blynk token"; // Auth Token from the Blynk App
char ssid[] = "Tuan Nguyen";  // WiFi SSID
char pass[] = "thangtri123";  // WiFi Password

#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE); 
BlynkTimer timer; // Blynk timer 

void sendSensor() {
  float h = dht.readHumidity();    // Read humidity from the DHT sensor
  float t = dht.readTemperature(); // Read temperature from the DHT sensor

  if (isnan(h) || isnan(t)) { // Check h and t is a number or not 
    Serial.println("Failed to read from DHT sensor!"); // If not a number , show this message 
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C, Humidity: "); // Print temperature and humidity values on the same line
  Serial.print(h);
  Serial.println(" %");

  Blynk.virtualWrite(V1, t); // Send temperature value to V1 in Blynk app
  Blynk.virtualWrite(V2, h); // Send humidity value to V2 in Blynk app
}

void setup() {
  Serial.begin(9600); // Set baudrate value 
  Blynk.begin(auth, ssid, pass); // Connect to Blynk using WiFi
  pinMode(D0, OUTPUT); // Device status 
 
  dht.begin();
  timer.setInterval(1000L, sendSensor); // Call sendSensor function every 1 second
}

void loop() {
  Blynk.run(); // Run Blynk
  timer.run(); // Run timer
}
