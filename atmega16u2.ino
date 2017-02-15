//#include "Keyboard.h"
#include "Mouse.h"
#include "HID.h"

const char PROGMEM keyboard_cmd[] = "KBD";
const char PROGMEM cdc_cmd[] = "CDC";
const char PROGMEM mouse_cmd[] = "MOUSE";

char buff[11];
uint8_t idx = 0;

void setup() {
  while (!Serial);
  Serial.begin(0);
  Serial1.begin(9600);

  // Keyboard.begin();
  Mouse.begin();
}

void (*serialFct)(void) = NULL;

void serialMouse() {
  if (!Serial1.available())
    return;
  if (Serial1.peek() == 27) {
    Serial1.read();
    serialFct = NULL;
    return;
  }
  if (!(idx = Serial1.readBytesUntil('\n', buff, 10)))
    return;
  buff[idx] = '\0';

  char sign = 1;
  char x = 0;
  char y = 0;
  char *ptr = buff;

  if (*ptr == '-') {
    sign = -1;
    ptr++;
  }
  while (*ptr != ';' && *ptr) {
    x *= 10;
    x += (*ptr - '0');
    ptr++;
  }
  x *= sign;
  sign = 1;
  if (!(*ptr))
    return;
  ptr++;
  if (*ptr == '-') {
    sign = -1;
    ptr++;
  }
  while (*ptr) {
    y *= 10;
    y += (*ptr - '0');
    ptr++;
  }
  y *= sign;
  Mouse.move(x, y);
  delay(100);
}

void serialCDC() {
  char c = 0;

  while (Serial1.available()) {
    if ((c = Serial1.read()) == 27) {
      serialFct = NULL;
      return;
    }
    Serial.write(c);
  }
}

/* void serialKeyboard() {
  char c = 0;
  
  while (Serial1.available()) {
    if ((c = Serial1.read()) == 27) {
      serialFct = NULL;
      return;
    }
    Keyboard.print(c);
    delay(10);
  }
} */

bool parseSerialFct() {
  if (!Serial1.available() || !(idx = Serial1.readBytesUntil('\n', buff, 10)))
    return false;
  buff[idx - 1] = '\0';
  /* Serial.print(F("Debug : "));
  Serial.println(buff);
  if (!strcasecmp_P(buff, keyboard_cmd))
    serialFct = serialKeyboard;
  else */if (!strcasecmp_P(buff, cdc_cmd))
    serialFct = serialCDC;
  else if (!strcasecmp_P(buff, mouse_cmd))
    serialFct = serialMouse;
}

void loopSerial() {
  if (Serial1.available()) {
    // If no serial command is configured, then parse one from serial input
    if (serialFct == NULL && !parseSerialFct()) {
      Serial1.end();
      Serial1.begin(9600);
      return;
    }

    serialFct();
  }
}

void loop() {
  loopSerial();
}

