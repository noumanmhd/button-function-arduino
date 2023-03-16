#pragma once

#include <Arduino.h>
#include <vector>

constexpr unsigned int GAP_DELAY = 500;
constexpr unsigned int TAP_MAX_DELAY = 400;
constexpr unsigned int SAMPLES_SIZE = 20;
constexpr unsigned int SAMPLES_DELAY = 1;

using voidFunc = void (*)();

class ButtonFunction {
  public:
    ButtonFunction(const byte pin, const bool activeHigh = true, const bool usePullUp = true);

    void begin();
    void attachTap(voidFunc func, const byte n_tap = 1);
    void attachLongPress(voidFunc func, const byte n_hold = 1);
    void attachTapAndPress(voidFunc func, const byte n_tap = 1, const byte n_hold = 1);
    void scan();
    void setGapDelay(const unsigned int gapDelay);
    void setMaxTapDelay(const unsigned int maxTapDelay);

  private:
    const byte m_pin;
    const bool m_activeHigh;
    const bool m_usePullUp;
    unsigned long m_lastPressedTime = 0;
    unsigned long m_maxTapDelay = TAP_MAX_DELAY;
    unsigned long m_gapDelay = GAP_DELAY;
    byte m_numTaps = 0;
    byte m_numHolds = 0;

    struct Record {
        byte n_tap = 0;
        byte n_hold = 0;
        voidFunc func = nullptr;
    };
    std::vector<Record> m_records;

    void addRecord(const byte n_tap, const byte n_hold, voidFunc func);
    void clearRecords();
    bool readInput();
    unsigned long pressRoutine();
    bool isPressed();
};
