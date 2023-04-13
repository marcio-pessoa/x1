/* x1.ino, x1 Mark I - Useless Machine, Arduino main sketch file
 *
 * Copyright 2019-2023 Marcio Pessoa
 *
 * This sketch was developed and tested on: Arduino Leonardo
 * I also tested on: Arduino Uno
 * To work on other Arduino models, some adaptations may be necessary.
 *
 * Author: Márcio Pessoa <marcio.pessoa@gmail.com>
 * Contributors: none
 */

#include <Alarm.h>       // Marcio Pessoa - Manage alarms
#include <Arduino.h>     // Arduino - Main library
#include <Axis.h>        // Marcio Pessoa - Motor axis
#include <Blinker.h>     // Marcio Pessoa - Blink leds nicely
#include <Debounce2.h>   // Marcio Pessoa - Debounce for switch
#include <Help.h>        // Marcio Pessoa - Help messages builder
#include <MemoryFree.h>  //
#include <Project.h>     // Marcio Pessoa - Basic project definitions
#include <Servo.h>       // Arduino - Servo Motor
#include <Switch.h>      // Marcio Pessoa - Switch manipulation
#include <Timer.h>       // Marcio Pessoa - Timer library
#include <math.h>        // Arduino - Math functions
#include "./config.h"    // Marcio Pessoa - Configuration

// Project definitions
Project x1("x1",                                        // Platform
           "I",                                         // Mark
           "Useless Machine",                           // Name
           "1.30.0",                                    // Version
           "2023-04-12",                                // Version date
           "4",                                         // Serial number
           "Copyright (c) 2015-2023 Marcio Pessoa",     // Owner
           "undefined. There is NO WARRANTY.",          // License
           "https://github.com/marcio-pessoa/x1",       // Website
           "Marcio Pessoa <marcio.pessoa@gmail.com>");  // Contact

// Status LED
Blinker status_led(led_status_pin);

// Power relay
Switch relay(relay_pin);

// Lever switch
int lever_counter = 0;
bool lever_last_state = LOW;
Debounce2 lever;

// Axis
Axis finger("finger",             // Name
            servo_pin,            // Electronic identifier
            position_switch_off,  // Minimum hard position
            position_park,        // Maximum hard position
            position_switch_off,  // Minimum soft position
            position_park,        // Maximum soft position
            position_park,        // Park position
            servo_offset_delay);  // Move delay

// Servo motors
Servo servo;

// Finger delay
Timer action((unsigned long)action_timer, COUNTDOWN);

// Standby timer
Timer standby((unsigned long)standby_timer * 1000, COUNTDOWN);

void setup() {
  // Serial interface
  Serial.begin(serial_speed);
  // Start up message
  Serial.println("Starting...");
  CommandM92();  // Version information
  // Random number generator seed
  pinMode(random_Seed_pin, INPUT);
  randomSeed(analogRead(random_Seed_pin));
  // Lever switch
  lever.attach(lever_pin, 70, 0);  // Set debounce to 70 milliseconds
  // Attach servo motor
  CommandM17();  // Attach motor
  // G-code ready to receive commands
  GcodeReady();
}

void loop() {
  NotificationHandler();
  SwitchHandler();
  FingerHandler();
  StandbyHandler();
  GcodeCheck();
}
