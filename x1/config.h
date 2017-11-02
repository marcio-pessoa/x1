/* config.h, x1 Mark I - Useless Machine, Arduino project config file
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

// LEDs
const byte led_status_pin = 13;
const byte led_angry_pin = 6;

// Speaker
const byte speaker_pin = 5;

// Lever
const byte lever_pin = 2;

// Power relay
const byte relay_pin = 3;

// Finger
const byte servo_pin = 9;
const byte position_park = 170;  // degree angle
const byte position_switch_off = 111;  // degree angle
const byte servo_delay = 20;  // milliseconds - maximum servo delay to be
                              // randomized
const byte servo_offset_delay = 6;  // milliseconds - offset added to servo
                                    // delay to be randomized

// Random number generator Seed
const byte random_Seed_pin = 5;

// Timers
const byte standby_timer = 20;  // seconds
const int action_timer = 2000;  // milliseconds - delay before finger action

// Debug mode
bool debug = false;

// Serial speed: 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200
const unsigned long serial_speed = 115200;
