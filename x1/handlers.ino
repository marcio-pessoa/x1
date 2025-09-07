/* handlers.ino, x1 Mark I - Useless Machine, Arduino handlers sketch file
 *
 * Copyright 2019-2020 Marcio Pessoa
 *
 * Author: Márcio Pessoa <marcio.pessoa@gmail.com>
 * Contributors: none
 */

/**
 * @brief Handles notifications, like blinking the status LED.
 */
void NotificationHandler() {
  status_led.blink();
}

/**
 * @brief Handles the lever switch.
 * This function checks the state of the lever switch and calls the
 * appropriate function to turn the switch off or park the finger.
 */
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

/**
 * @brief Handles the finger movement.
 * This function moves the finger and updates its position.
 */
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

/**
 * @brief Handles the standby timer.
 * This function checks the standby timer and turns the power off if the
 * machine is idle.
 */
void StandbyHandler() {
  if (standby.check() &&
      relay.status() &&
      finger.positionRead() == position_park) {
    CommandM82();  // Power off
  }
}
