/*
  Name: WiFi WebServer
  Board: esp32 -> ESP32S3 Dev Module / DevKit
  Hardware: ayatec sensoraya v2.1

  Description:
  Maintains connection to local network via WiFi.
  Answers to root HTTP requests.

  Pin usage:
  - N/A

  Dependencies:
  - N/A

  Created: 2026-02-08
  Author: ayatec (Michal Liptak)
  License: MIT
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// Set your MQTT and WiFi connection details here:
#define WIFI_SSID         ""
#define WIFI_PASSWORD     ""

#define MESSAGE           "Hello from sensoraya"

WebServer wifiServer(80);
unsigned long Ref2s;  // non-blocking sketch timestamps

void setup(){
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  wifiServer.on("/", []() {  // return message on request
        Serial.print("[HTTP] ");
        Serial.println(MESSAGE);
        wifiServer.send(200, "text/plain", MESSAGE);
      });
  wifiServer.begin();

  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      } 
  Serial.print("\nWebserver available on ");
  Serial.println(WiFi.localIP());
}

void loop(){
wifiServer.handleClient();
delay(0);          // required in minimal example to avoid wdt reboot
}
