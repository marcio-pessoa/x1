/* handlers.ino, x1 Mark I - Useless Machine, Arduino handlers sketch file
 *
 * Copyright 2019-2020 Marcio Pessoa
 *
 * Author: Márcio Pessoa <marcio.pessoa@gmail.com>
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
    } else {
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
  if (finger.isDone() && done == false) {
    done = true;
    status(false);
  }
}

void StandbyHandler() {
  if (standby.check() &&
      relay.status() &&
      finger.positionRead() == position_park) {
    CommandM82();  // Power off
  }
}
