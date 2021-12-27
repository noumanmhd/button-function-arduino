#include "buttonfunc.h"

BTN_RECORD::BTN_RECORD(byte t, byte h, voidFunc f) {
  tap = t;
  hold = h;
  func = f;
  next = nullptr;
}

ButtonFunction::ButtonFunction(byte p) {
  t = dt = tap = hold = 0;
  record = nullptr;
  pin = p;
  max_tap_delay = TAP_MAX_DELAY;
  gap_delay = GAP_DELAY;
}

void ButtonFunction::addRecord(byte t, byte h, voidFunc func) {
  BTN_RECORD *newRecord = new BTN_RECORD(t, h, func);

  if (record == nullptr) {
    record = newRecord;
  } else {
    BTN_RECORD *tempRecord = record;
    while (tempRecord->next != nullptr) {
      tempRecord = tempRecord->next;
    }
    tempRecord->next = newRecord;
  }
}

void ButtonFunction::clearRecord() {
  BTN_RECORD *current = record;
  BTN_RECORD *next = nullptr;
  record = nullptr;
  while (current != nullptr) {
    next = current->next;
    delete current;
    current = next;
  }
}

void ButtonFunction::begin() {
  clearRecord();
  on_state = true;
  pinMode(pin, INPUT);
}

void ButtonFunction::begin(bool btn_on_state) {
  clearRecord();
  on_state = btn_on_state;
  if (on_state) {
    pinMode(pin, INPUT);
  } else {
    pinMode(pin, INPUT_PULLUP);
  }
}

void ButtonFunction::begin(bool on_state, bool pullup) {
  clearRecord();
  on_state = on_state;
  if (pullup) {
    pinMode(pin, INPUT_PULLUP);
  } else {
    pinMode(pin, INPUT);
  }
}

bool ButtonFunction::readInput() {
  double sum = 0;
  for (int i = 0; i < SAMPLES_SIZE; i++) {
    sum += (digitalRead(pin) == on_state);
    delay(SAMPLES_DELAY);
  }
  sum = round(sum / SAMPLES_SIZE);
  return (sum == 1);
}

unsigned long ButtonFunction::pressRoutine() {
  unsigned long hold_t = millis();
  while (readInput())
    ;
  hold_t = millis() - hold_t;
  return hold_t;
}

void ButtonFunction::scan() {
  bool state = true;
  while (state) {
    dt = millis() - t;
    if (readInput()) {
      unsigned int press_time = pressRoutine();
      if (press_time < max_tap_delay) {
        tap++;
      } else {
        hold++;
      }
      t = millis();
      dt = 0;
      state = true;
    } else {
      state = false;
    }

    if (dt > gap_delay) {
      state = false;
      if (tap > 0 || hold > 0) {
        BTN_RECORD *current = record;
        while (current != nullptr) {
          if ((tap == current->tap) && (hold == current->hold)) {
            current->func();
          }
          current = current->next;
        }

        tap = 0;
        hold = 0;
      }
    }
  }
}

void ButtonFunction::setGapDelay(unsigned long t) { gap_delay = t; }

void ButtonFunction::setMaxTapDelay(unsigned long t) { max_tap_delay = t; }

void ButtonFunction::attachTap(voidFunc func, byte times) {
  addRecord(times, 0, func);
}
void ButtonFunction::attachLongPress(voidFunc func, byte times) {
  addRecord(0, times, func);
}
void ButtonFunction::attachTapAndPress(voidFunc func, byte n_tap,
                                       byte n_press) {
  addRecord(n_tap, n_press, func);
}
