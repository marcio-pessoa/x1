/* handlers.ino, x1 Mark I - Useless Machine, Arduino handlers sketch file
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

void NotificationHandler() {
  status_led.blink();
}

void SwitchHandler() {
  bool lever_state = lever.check();
  if (lever_state != lever_last_state) {
    lever_last_state = lever_state;
    if (lever_state == HIGH) {
      TurnSwitchOff();
    }
    else {
      ParkFinger();
    }
  }
}

void FingerHandler() {
  if (action.check()) {
    finger.run();
  }
  if (relay.status()) {
    servo.write(finger.positionRead());
  }
}

void StandbyHandler() {
  if (standby.check() and 
      relay.status() and 
      finger.positionRead() == position_park) {
    CommandM82();
  }
}
