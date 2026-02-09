/*
  Name: Buzzer – Boot Beep
  Board: esp32 -> ESP32S3 Dev Module / DevKit
  Hardware: ayatec sensoraya v2.1

  Description:
  Beeps shortly with the on-board buzzer once after each boot.

  Pin usage:
  - GPIO14 - Passive buzzer (see sensoraya v2.1 schematic)

  Dependencies:
  - N/A

  Created: 2026-02-09
  Author: ayatec (Michal Liptak)
  License: MIT
*/


#define PIN_BUZZER   14
#define BEEP_TIME    150   // milliseconds
#define BEEP_DUTY    30   // 0–255 (volume)
#define BEEP_FREQ    2000  // Hz

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(PIN_BUZZER, OUTPUT);
  analogWriteFrequency(BEEP_FREQ);
  analogWrite(PIN_BUZZER, BEEP_DUTY);  // buzzer on
  delay(BEEP_TIME);
  analogWrite(PIN_BUZZER, 0);  // buzzer off
  Serial.println("BEEEEP!\nReboot for another beep.");
}

void loop(){
 delay(1);          // required in minimal example to avoid wdt reboot
}
