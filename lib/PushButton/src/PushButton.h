#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H
#include <Arduino.h>
#include "types.h"

class PushButton
{
public:
    bool state = false;
    void init(RelayTogglerFn toggleFn, uint8_t pin);
    void toggle();
    void turnOn();
    void turnOff();
    void wasPushed();

private:
    RelayTogglerFn relayTogglerFn;
    u_int8_t buttonPin;
    bool lastButtonState = HIGH;
};

#endif