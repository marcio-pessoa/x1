/* commands.ino, x1 Mark I - Useless Machine, Arduino commands sketch file
 *
 * Copyright 2019-2020 Marcio Pessoa
 *
 * Author: Márcio Pessoa <marcio.pessoa@gmail.com>
 * Contributors: none
 */

/**
 * @brief Displays a help message with all available G-code and M-code commands.
 *
 * @param letter [char] 'G' to show only G-codes, 'M' to show only M-codes, or 0
 * to show all.
 * @return bool Returns false for success.
 */
bool CommandM100(char letter = 0) {
  if (letter == 'G' || letter == 0) {
    echoln(F("G0\tMove axis"));
    echoln(F("G03\tFinger delay"));
    echoln(F("G28\tFinger home"));
    echoln(F("G29\tFinger out-of-door"));
    echoln(F("G90\tAbsolute programming"));
    echoln(F("G91\tIncremental programming"));
  }
  if (letter == 'M' || letter == 0) {
    echoln(F("M0\tStop"));
    echoln(F("M15\tSystem information"));
    echoln(F("M17\tAttach motor"));
    echoln(F("M18\tDetach motor"));
    echoln(F("M80\tPower status"));
    echoln(F("M81\tPower on"));
    echoln(F("M82\tPower off"));
    echoln(F("M86\tAxis information"));
    echoln(F("M89\tMemory information"));
    echoln(F("M90\tLever status"));
    echoln(F("M92\tSystem version"));
    echoln(F("M99\tReset system"));
    echoln(F("M100\tThis help message"));
    echoln(F("M111\tDebug mode"));
  }
  return false;  // Success
}

/**
 * @brief Set axis to absolute programming.
 *
 * @return bool Returns false for success.
 */
bool CommandG90() {
  finger.absolute(true);
  return false;  // Success
}

/**
 * @brief Set axis to incremental programming.
 *
 * @return bool Returns false for success.
 */
bool CommandG91() {
  finger.absolute(false);
  return false;  // Success
}

/**
 * @brief Displays axis information.
 *
 * @return bool Returns false for success.
 */
bool CommandM86() {
  echoln(String("Finger position: ") + "(" + String(finger.positionRead()) +
         ")");
  echoln(String("Finger delay: ") + "(" + String(finger.delayRead()) + ")");
  return false;  // Success
}

/**
 * @brief Attach servo motor.
 *
 * @return bool Returns false for success.
 */
bool CommandM17() {
  servo.attach(finger.pinRead());
  servo.write(finger.positionRead());
  return false;  // Success
}

/**
 * @brief Move finger to switch off position.
 *
 * @return bool Returns false on success, true on failure (if relay is off).
 */
bool CommandG29() {
  if (!relay.status()) {
    done = true;
    status(true);
    return true;  // Failure
  }
  done = false;
  standby.reset();
  CommandG90();  // Absolute programming
  finger.positionWrite(position_switch_off);
  return false;  // Success
}

/**
 * @brief Move finger to park position.
 *
 * @return bool Returns false on success, true on failure (if relay is off).
 */
bool CommandG28() {
  if (!relay.status()) {
    done = true;
    status(true);
    return true;  // Failure
  }
  done = false;
  standby.reset();
  CommandG90();  // Absolute programming
  finger.positionWrite(position_park);
  return false;  // Success
}

/**
 * @brief Move finger to a specific position.
 *
 * @param x [int] The position to move to.
 * @return bool Returns false on success, true on failure (if relay is off).
 */
bool CommandG0(int x) {
  if (!relay.status()) {
    done = true;
    status(true);
    return true;  // Failure
  }
  standby.reset();
  done = false;
  finger.positionWrite(x);
  return false;  // Success
}

/**
 * @brief Stop finger movement.
 *
 * @return bool Returns false for success.
 */
bool CommandM0() {
  finger.positionWrite(finger.positionRead());
  return false;  // Success
}

/**
 * @brief Toggle debug mode.
 *
 * @return bool Returns false for success.
 */
bool CommandM111() {
  debug = !debug;
  echoln("Debug mode: " + String(debug ? "Yes" : "No"));
  return false;  // Success
}

/**
 * @brief Detach servo motor.
 *
 * @return bool Returns false for success.
 */
bool CommandM18() {
  servo.detach();
  return false;  // Success
}

/**
 * @brief Displays power status.
 *
 * @return bool Returns false for success.
 */
bool CommandM80() {
  echoln("Power: " + String(relay.status() ? "On" : "Off"));
  return false;  // Success
}

/**
 * @brief Turn power on.
 *
 * @return bool Returns true on success, false on failure.
 */
bool CommandM81() {
  relay.on();
  standby.reset();
  if (debug) {
    CommandM80();  // Power status
  }
  return !relay.status();
}

/**
 * @brief Turn power off.
 *
 * @return bool Returns true on success, false on failure.
 */
bool CommandM82() {
  if (finger.positionRead() == position_park) {
    CommandM0();  // Stop
    lever_counter = 0;
    servo_speed = 0;
    relay.off();
    if (debug) {
      CommandM80();  // Power status
    }
  }
  return relay.status();
}

/**
 * @brief Displays lever status and finger speed.
 *
 * @return bool Returns false for success.
 */
bool CommandM90() {
  echoln("Lever: " + String(lever.check() ? "On" : "Off"));
  echoln("    Speed: " + String(servo_speed * 100) + " cm/s");
  return false;  // Success
}

/**
 * @brief Displays system information.
 *
 * @return bool Returns false for success.
 */
bool CommandM15() {
  CommandM92();  // Version information
  CommandM89();  // Memory information
  CommandM80();  // Power status
  CommandM90();  // Lever status
  CommandM86();  // Axis information
  return false;  // Success
}

/**
 * @brief Set finger delay.
 *
 * @param x [int] The delay in milliseconds.
 * @return bool Returns false for success.
 */
bool CommandG3(int x) {
  finger.delayWrite(x);
  return false;  // Success
}

/**
 * @brief Displays memory information.
 *
 * @return bool Returns false for success.
 */
bool CommandM89() {
  int total = SRAM_TOTAL;
  int free = freeMemory();
  int used = total - free;
  int percent = (float)used * 100 / total;
  //
  Alarm memory(MEMORY_WARNING_LEVEL, MEMORY_CRITICAL_LEVEL);
  memory.nameWrite("Memory");
  memory.unitWrite("%");
  memory.check(percent);
  //
  echoln(memory.nameRead() + " (" + memory.status_name() + "): " + percent +
         memory.unitRead() + " used");
  if (debug) {
    echoln("  SRAM:\t" + String(total) + " B\n" + "  Used:\t" + used +
           " B\n" + "  Free:\t" + free + " B\n" + "  Warning: " +
           memory.max_warningRead() + memory.unitRead() + "\n" +
           "  Critical: " + memory.max_criticalRead() + memory.unitRead());
  }
  return false;  // Success
}

/**
 * @brief Reset system.
 *
 * @return bool Returns false for success.
 */
bool CommandM99() {
  echoln(F("Reseting...\n"));
  CommandM18();  // Detach motor
  x1.reset();
  return false;  // Success
}

/**
 * @brief Displays system version.
 *
 * @return bool Returns false for success.
 */
bool CommandM92() {
  echoln(x1.version());
  if (debug || (millis() < 1000)) {
    echoln(x1.owner());
    echoln(x1.compiled());
    echoln(x1.license());
    echoln(x1.website());
    echoln(x1.contact());
  }
  return false;  // Success
}

/**
 * @brief Displays an "Unknown command" message.
 *
 * @return bool Returns false for success.
 */
bool Command0() {
  echoln(F("Unknown command"));
  return false;  // Success
}
