/* config.h, x1 Mark I - Useless Machine, Arduino project config file
 *
 * Copyright 2019-2020 Marcio Pessoa
 *
 * Author: Márcio Pessoa <marcio.pessoa@gmail.com>
 * Contributors: none
 */

// LEDs
const byte led_status_pin = 13;
const byte led_angry_pin = 6;

// Speaker
const byte speaker_pin = 5;

// Lever
const byte lever_pin = 2;
const int lever_debounce_time = 70; // milliseconds
const int lever_debounce_mode = 0; // 0 = normal, 1 = inverted

// Power relay
const byte relay_pin = 3;

// Finger
const byte servo_pin = 9;
const byte position_park = 170;  // degree angle
const byte position_switch_off = 111;  // degree angle
const byte servo_delay = 40;  // milliseconds - maximum servo delay
const byte servo_offset_delay = 6;  // milliseconds - servo speed offset
float servo_speed = 0;

// Random number generator Seed
const byte random_Seed_pin = 5;

// Timers
const byte standby_timer = 20;  // seconds
const int action_timer = 2000;  // milliseconds - delay before finger action

// Debug mode
bool debug = false;

// Serial speed: 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200
const unsigned long serial_speed = 115200;

// Move done
bool done = true;

// Sounds
const int TONE_SWITCH_OFF_FREQ = 2217;
const int TONE_SWITCH_OFF_DUR = 60;
const int TONE_PARK_FINGER_FREQ = 1217;
const int TONE_PARK_FINGER_DUR = 80;

// Memory
const float SRAM_TOTAL = 2.5 * 1024;
const int MEMORY_WARNING_LEVEL = 80;    // percent
const int MEMORY_CRITICAL_LEVEL = 90;  // percent

//
const float FLIMIT = 340282350000000000000000000000000000000;
