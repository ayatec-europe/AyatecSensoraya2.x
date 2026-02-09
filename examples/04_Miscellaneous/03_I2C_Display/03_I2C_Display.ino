/*
  Name: I2C Display
  Board: esp32 -> ESP32S3 Dev Module / DevKit
  Hardware: ayatec sensoraya v2.1

  Description:
  Connects to a 128x64 display via I2C.
  Initiates a 10-second count-down on a display.

  Pin usage:
  - I2C: IO39, IO40 (SCL/SDA, see sensoraya v2.1 schematic)

  Dependencies:
  - N/A

  Created: 2026-02-09
  Author: ayatec (Michal Liptak)
  License: MIT
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define PIN_SCL           39
#define PIN_SDA           40
#define SCREEN_WIDTH      128
#define SCREEN_HEIGHT     64
#define SCREEN_ADDRESS    0x3C  // (address 0x3C/0x3D for 128x64)
#define OLED_RESET        -1    // (not used)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int countdownSeconds = 10;

void setup()
 { 
  Serial.begin(115200);           // setting communication with PC

  Serial.println();
  Serial.println(F("Initializing Sensoraya Display Demo"));

  Wire.begin(PIN_SDA, PIN_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // initiates display - 
    Serial.println(F("SSD1306 allocation failed - display not working!"));
    while (true);     // Halt if display fails
    }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Start countdown
  for (int i = countdownSeconds; i >= 0; i--) {
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Countdown");

    display.setTextSize(3);
    display.setCursor(30, 30);
    display.print(i);

    display.display();
    delay(1000);
  }

  // Finished message
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(20, 25);
  display.println("DONE!");
  display.display();
  
}

void loop()
{
  delay(1); // keep watch dog happy
}
