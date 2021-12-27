#include <Arduino.h>

#ifndef BUTTON_FUNC_H
#define BUTTON_FUNC_H

#define GAP_DELAY 500
#define TAP_MAX_DELAY 400

#define SAMPLES_SIZE 20
#define SAMPLES_DELAY 1

typedef void (*voidFunc)(void);

class BTN_RECORD {
 public:
  byte tap;
  byte hold;
  voidFunc func;
  BTN_RECORD *next;
  BTN_RECORD(byte, byte, voidFunc);
};

class ButtonFunction {
 private:
  byte pin;
  bool on_state;
  unsigned long t;
  unsigned long dt;

  unsigned long gap_delay;
  unsigned long max_tap_delay;

  byte tap;
  byte hold;

  BTN_RECORD *record;
  unsigned int size;

  void addRecord(byte, byte, voidFunc);
  void clearRecord();

  bool readInput();
  unsigned long pressRoutine();

 public:
  ButtonFunction(byte);

  void begin();
  void begin(bool);
  void begin(bool, bool);

  void attachTap(voidFunc, byte times);
  void attachLongPress(voidFunc, byte times);
  void attachTapAndPress(voidFunc, byte n_tap, byte n_press);

  void scan();

  void setGapDelay(unsigned long);
  void setMaxTapDelay(unsigned long);
};

#endif