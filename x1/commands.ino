/* commands.ino, x1 Mark I - Useless Machine, Arduino commands sketch file
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM100(char letter = 0) {
  if (letter == 'G' or letter == 0) {
    echoln(F("G0\tMove axis"));
    echoln(F("G03\tFinger delay"));
    echoln(F("G28\tFinger home"));
    echoln(F("G29\tFinger out-of-door"));
    echoln(F("G90\tAbsolute programming"));
    echoln(F("G91\tIncremental programming"));
  }
  if (letter == 'M' or letter == 0) {
    echoln(F("M0\tStop"));  }
    echoln(F("M15\tSystem info"));
    echoln(F("M17\tAttach motor"));
    echoln(F("M18\tDetach motor"));
    echoln(F("M80\tPower status"));
    echoln(F("M81\tPower on"));
    echoln(F("M82\tPower off"));
    echoln(F("M86\tAxis information"));
    echoln(F("M89\tMemory information"));
    echoln(F("M90\tLever status"));
    echoln(F("M92\tSystem information"));
    echoln(F("M99\tReset system"));
    echoln(F("M100\tThis help message"));
    echoln(F("M111\tDebug mode"));
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandG90() {
  finger.absolute(true);
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandG91() {
  finger.absolute(false);
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM86() {
  echoln(String("Finger position: ") +
                 "(" + String(finger.positionRead()) + ")");
  echoln(String("Finger delay: ") +
                 "(" + String(finger.delayRead()) + ")");
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM17() {
  servo.attach(finger.pinRead());
  servo.write(finger.positionRead());
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandG29() {
  if (relay.status()) {
    standby.reset();
    finger.positionWrite(position_switch_off);
    return false;
  }
  else {
    return true;
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandG28() {
  if (relay.status()) {
    standby.reset();
    finger.positionWrite(position_park);
    return false;
  }
  else {
    return true;
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   false: OK
 *   true: Power off
 */
int CommandG0(int x) {
  if (relay.status()) {
    standby.reset();
    finger.positionWrite(x);
    return false;
  }
  else {
    return true;
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM0() {
  finger.positionWrite(finger.positionRead());
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM111() {
  debug = !debug;
  echoln("Debug mode: " + String(debug ? "Yes" : "No"));
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM18() {
  servo.detach();
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM80() {
  echoln("Power: " + String(relay.status() ? "On" : "Off"));
  return false;
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
bool CommandM81() {
  relay.on();
  standby.reset();
  if (debug) {
    CommandM80();  // Power status
  }
  return !relay.status();
}

/* CommandM82
 * 
 * Description
 *   Power off.
 * 
 *   CommandM82()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   bool
 */
bool CommandM82() {
  if (finger.positionRead() == position_park) {
    CommandM0();  // Stop
    relay.off();
    if (debug) {
      CommandM80();  // Power status
    }
  }
  return relay.status();
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM90() {
  echoln("Lever: " + String(lever.check() ? "On" : "Off"));
  echoln("    Speed: " + String(servo_speed * 100) + " cm/s");
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM15() {
  CommandM92();  // Version information
  CommandM89();  // Memory information
  CommandM80();  // Power status
  CommandM90();  // Lever status
  CommandM86();  // Axis information
}

/* 
 * 
 * Description
 *   Finger delay.
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandG3(int x) {
  finger.delayWrite(x);
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM89() {
  int total = 2.5 * 1024;
  int free = freeMemory();
  int used = total - free;
  int percent = (float)used * 100 / total;
  // 
  Alarm memory(80, 90);
  memory.nameWrite("Memory");
  memory.unitWrite("%");
  memory.check(percent);
  // 
  echoln(memory.nameRead() + " (" + memory.status_name() + "): " + 
         percent + memory.unitRead() + " used");
  if (debug) {
    echoln("  SRAM:\t" + String(total) + " B\n" +
           "  Used:\t" + used + " B\n" +
           "  Free:\t" + free + " B\n" +
           "  Warning: " + memory.max_warningRead() + memory.unitRead() + "\n" +
           "  Critical: " + memory.max_criticalRead() + memory.unitRead());
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM99() {
  echoln(F("Reseting...\n"));
  CommandM18();  // Detach motor
  x1.reset();
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int CommandM92() {
  echoln(x1.version());
  if (debug or (millis() < 100)) {
    echoln(x1.owner());
    echoln(x1.compiled());
    echoln(x1.license());
    echoln(x1.website());
    echoln(x1.contact());
  }
}

/* 
 * 
 * Description
 *   .
 * 
 *   ()
 * 
 * Parameters
 *   none
 * 
 * Returns
 *   void
 */
int Command0() {
  echoln(F("Unknown command")); 
}
