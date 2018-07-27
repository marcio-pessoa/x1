/* x1.ino, x1 Mark I - Useless Machine, Arduino main sketch file
 * 
 * This sketch was developed and tested on: Arduino Leonardo
 * I also tested on: Arduino Uno
 * To work on other Arduino models, some adaptations may be necessary.
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

#include <Arduino.h>         // Arduino - Main library
#include <Servo.h>           // Arduino - Servo Motor
#include <math.h>            // Arduino - Math functions
#include <Project.h>         // Sciemon - Basic project definitions
#include <Help.h>            // Sciemon - Help messages builder
#include <Debounce.h>        // Sciemon - Debounce for switch
#include <Blinker.h>         // Sciemon - Blink leds nicely
#include <Alarm.h>           // Sciemon - Manage alarms
#include <Timer.h>           // Sciemon - Timer library with nice features
#include <Switch.h>          // Sciemon - Switch manipulation
#include <Axis.h>            // Sciemon - Motor axis
#include "config.h"          // Sciemon - Configuration
#include <MemoryFree.h>      // 

// Project definitions
Project x1("x1",  // Platform
           "I",  // Mark
           "Useless Machine",  // Name
           "0.21b",  // Version
           "2018-07-27",  // Version date
           "4",  // Serial number
           "Copyright (c) 2015-2018 Marcio Pessoa",  // Owner
           "undefined. There is NO WARRANTY.",  // License
           "http://pessoa.eti.br/",  // Website
           "Marcio Pessoa <marcio@pessoa.eti.br>");  // Contact

// Status LED
Blinker status_led(led_status_pin);

// Power relay
Switch relay(relay_pin);

// Lever switch
int lever_counter = 0;
bool lever_last_state = LOW;
Debounce lever(lever_pin);

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
  lever.set(70);  // Set debounce to 70 milliseconds
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
