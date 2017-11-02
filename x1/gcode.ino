/* gcode.ino, x1 Mark I - Useless Machine, G-code parser sketch file
 * 
 * Author: Márcio Pessoa <marcio.pessoa@sciemon.com>
 * Contributors: none
 */

#define BUFFER_SIZE 48

char buffer[BUFFER_SIZE];
int buffer_pointer = 0;

void status(bool i) {
  Serial.println(i == false ? F("ok") : F("nok"));
}

bool echo(String message) {
  Serial.print(message);
}

bool echoln(String message) {
  echo(message + "\n");
}

void GcodeReady() {
  buffer_pointer = 0;
}

void GcodeCheck() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (buffer_pointer < BUFFER_SIZE-1) {
      buffer[buffer_pointer++] = c;
    }
    if (c == '\n') {
      buffer[buffer_pointer] = 0;
      GCodeParse();
      GcodeReady();
    }
  }
}

float GCodeNumber(char code, float val) {
  char *ptr = buffer;
  while(ptr && *ptr && ptr < buffer + buffer_pointer) {
    if(*ptr == code) {
      return atof(ptr + 1);
    }
    ptr = strchr(ptr, ' ') + 1;
  }
  return val;
}

void GCodeParse() {
  bool retval = false;
  char letter = buffer[0];
  byte number = GCodeNumber(letter, -1);
  switch (letter) {
    case 'G':
      switch (number) {
        case 0:
        case 1:
          retval = CommandG0(GCodeNumber('X', 0));
          break;
        case 3:
          retval = CommandG3(GCodeNumber('X', 0));
          break;
        case 28:
          retval = CommandG28();
          break;
        case 29:
          retval = CommandG29();
          break;
        case 90:
          retval = CommandG90();
          break;
        case 91:
          retval = CommandG91();
          break;
        default:
          retval = Command0();
          break;
      }
      break;
    case 'M':
      switch(number) {
        case 0:
          retval = CommandM0();
          break;
        case 15:
          retval = CommandM15();
          break;
        case 17:
          retval = CommandM17();
          break;
        case 18:
        case 84:
          retval = CommandM18();
          break;
        case 80:
          retval = CommandM80();
          break;
        case 81:
          retval = CommandM81();
          break;
        case 82:
          retval = CommandM82();
          break;
        case 86:
          retval = CommandM86();
          break;
        case 89:
          retval = CommandM89();
          break;
        case 90:
          retval = CommandM90();
          break;
        case 92:
          retval = CommandM92();
          break;
        case 99:
          retval = CommandM99();
          break;
        case 100:
          retval = CommandM100();
          break;
        case 111:
          retval = CommandM111();
          break;
        default:
          retval = Command0();
          break;
      }
      break;
    default:
      if (buffer_pointer > 2) {
        Command0();
      }
      break;
  }
  if (buffer_pointer > 2) {
    status(retval);
  }
}
