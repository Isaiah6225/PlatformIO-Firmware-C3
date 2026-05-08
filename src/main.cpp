#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_BME680.h>
#include "config.h"

WiFiUDP udp;
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

void setup() {
    delay(2000);
    Serial.begin(115200);
    Serial.println("\n--- STARTING AP MODE TEST ---");

    // Bus Hygiene
    pinMode(OTHER_CS, OUTPUT);
    digitalWrite(OTHER_CS, HIGH); 

    // Set up the Access Point
    // SoftAP(ssid, password, channel, hidden, max_connection)
    WiFi.softAP(AP_SSID, AP_PASS);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP Interface Started. SSID: ");
    Serial.println(AP_SSID);
    Serial.print("IP Address: ");
    Serial.println(IP);

    if (!bme.begin()) {
        Serial.println("BME680 Failed! Check SPI Pins 5,6,7,8.");
    }
}

void loop() {
    if (bme.performReading()) {
        // Construct the CSV string
        String data = String(millis()) + "," + 
                      String(bme.temperature) + "," + 
                      String(bme.humidity) + "," + 
                      String(bme.pressure / 100.0) + "," + 
                      String(bme.gas_resistance / 1000.0);
        
        // Broadcast to anyone connected to the AP
        udp.beginPacket(UDP_IP, UDP_PORT);
        udp.print(data);
        udp.endPacket();

        Serial.println("Broadcasted: " + data);
    }
    delay(POLLING_RATE_MS); 
}