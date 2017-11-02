/* auxiliar.ino, x1 Mark I - Useless Machine, Arduino auxiliar sketch file
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

void TurnSwitchOff() {
  tone(speaker_pin, 2217, 60);
  digitalWrite(led_angry_pin, HIGH);
  lever_counter++;
  // Set delay before finger action and reset timer
  action.set(random(ceil(action_timer) + 100));
  action.reset();
  // Set finger delay (or speed)
  finger.delayWrite(ceil(random(servo_delay) + servo_offset_delay));
  standby.reset();  // Reset standby timer
  // Turn on relay
  if (relay.status() == LOW) {
    CommandM81();  // Power on
  }
  CommandG90();  // Absolute programming
  finger.positionWrite(position_switch_off);
  if (debug) {
    CommandM90();  // Lever status
  }
}

void ParkFinger() {
  tone(speaker_pin, 1217, 80);
  digitalWrite(led_angry_pin, LOW);
  finger.positionWrite(position_park);
  finger.delayWrite(ceil(random(servo_delay) + servo_offset_delay));
  if (debug) {
    CommandM90();  // Lever status
  }
}
