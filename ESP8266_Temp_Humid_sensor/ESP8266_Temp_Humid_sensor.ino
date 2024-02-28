#define BLYNK_TEMPLATE_ID "TMPL6knRUNNWy" // Template ID
#define BLYNK_TEMPLATE_NAME "Temperature and humidity sensor" // Template name

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD

#include "DHT.h" // DHT library
#include "BlynkEdgent.h"

#define DHTPIN 4       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE); 
BlynkTimer timer; // Blynk timer 

void sendSensor() {
  float h = dht.readHumidity();    // Read humidity from the DHT sensor
  float t = dht.readTemperature(); // Read temperature from the DHT sensor

  if (!isnan(h) && !isnan(t)) { // Check if h and t are valid numbers
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" °C, Humidity: ");
    Serial.print(h);
    Serial.println(" %");

    Blynk.virtualWrite(V1, t); // Send temperature value to V1 in Blynk app
    Blynk.virtualWrite(V2, h); // Send humidity value to V2 in Blynk app
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
}

void setup() {
  Serial.begin(9600);
  BlynkEdgent.begin();
  pinMode(D0, OUTPUT); // Device status indicator
  dht.begin();
  timer.setInterval(1000L, sendSensor); // Call sendSensor function every 5 seconds
}

void loop() {
  BlynkEdgent.run();
  timer.run(); // Run Blynk timer
}
