/*
  Name: MOSFET_Fader
  Board: esp32 -> ESP32S3 Dev Module / DevKit
  Hardware: ayatec sensoraya v2.1

  Description:
  Continuously fades the 8 on-board MOSFET outputs (P1-P8) in 
  and out using PWM. Demonstrates MOSFET functionality and basic 
  PWM control.

  Pin usage:
  - MOSFET outputs: IO15–IO20, IO3, IO46 (outputs P1–P8, diodes D9–D16, see sensoraya v2.1 schematic)

  Created: 2026-02-02
  Author: ayatec (Michal Liptak)
  License: MIT
*/

// MOSFET pins
constexpr uint8_t MOSFET_PINS[] = {15,16,17,18,19,20,3,46};
constexpr uint8_t NUM_MOSFETS = 8;

// PWM settings
constexpr uint32_t PWM_FREQ = 5000;      // 5 kHz
constexpr uint16_t PWM_RESOLUTION = 10;   // 10-bit, 0-1023

void setup() { // Initialize MOSFET pins for PWM
  for (uint8_t i=0; i<NUM_MOSFETS; i++) {
    ledcSetup(i, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(MOSFET_PINS[i], i);
  }
}

void loop() {
  // Fade up
  for (uint16_t duty=0; duty<=1023; duty++) {
    for (uint8_t i=0; i<NUM_MOSFETS; i++) {
      ledcWrite(i, duty);
    }
    delay(2);
  }

  // Fade down
  for (int16_t duty=1023; duty>=0; duty--) {
    for (uint8_t i=0; i<NUM_MOSFETS; i++) {
      ledcWrite(i, duty);
    }
    delay(2);
  }
}
