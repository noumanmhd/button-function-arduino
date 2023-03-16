#include "buttonfunc.h"

ButtonFunction::ButtonFunction(const byte pin, const bool activeHigh, const bool usePullUp)
    : m_pin(pin), m_activeHigh(activeHigh), m_usePullUp(usePullUp)
{}

void ButtonFunction::begin()
{
    m_lastPressedTime = 0;
    m_numTaps = 0;
    m_numHolds = 0;
    pinMode(m_pin, m_usePullUp ? INPUT_PULLUP : INPUT);
}

void ButtonFunction::attachTap(voidFunc func, const byte n_tap)
{
    addRecord(n_tap, 0, func);
}

void ButtonFunction::attachLongPress(voidFunc func, const byte n_hold)
{
    addRecord(0, n_hold, func);
}

void ButtonFunction::attachTapAndPress(voidFunc func, const byte n_tap, const byte n_hold)
{
    addRecord(n_tap, n_hold, func);
}

void ButtonFunction::scan(){
    if (isPressed())
    {
        const unsigned long now = millis();
        const unsigned long pressDuration = pressRoutine();
        const bool tap = pressDuration < m_maxTapDelay;
        m_numTaps += tap;
        m_numHolds += !tap;
        m_lastPressedTime = now;

        for (auto& r : m_records)
        {
            if (m_numTaps == r.n_tap && m_numHolds == r.n_hold)
            {
                r.func();
            }
        }
    }
    else if (millis() - m_lastPressedTime >= m_gapDelay)
    {
        m_numTaps = 0;
        m_numHolds = 0;
    }
}

void ButtonFunction::setGapDelay(const unsigned int gapDelay)
{
    m_gapDelay = gapDelay;
}

void ButtonFunction::setMaxTapDelay(const unsigned int maxTapDelay)
{
    m_maxTapDelay = maxTapDelay
}

void ButtonFunction::addRecord(const byte n_tap, const byte n_hold, voidFunc func)
{
m_records.push_back({ n_tap, n_hold, func });
}

void ButtonFunction::clearRecords()
{
m_records.clear();
}

bool ButtonFunction::readInput()
{
unsigned int sum = 0;
for (byte i = 0; i < SAMPLES_SIZE; i++)
{
sum += digitalRead(m_pin) == m_activeHigh;
delay(SAMPLES_DELAY);
}
return sum > SAMPLES_SIZE / 2;
}

unsigned long ButtonFunction::pressRoutine()
{
unsigned long holdDuration = 0;
while (isPressed())
{
holdDuration = millis() - m_lastPressedTime;
delay(SAMPLES_DELAY);
}
return holdDuration;
}

bool ButtonFunction::isPressed()
{
return digitalRead(m_pin) == m_activeHigh;
}
