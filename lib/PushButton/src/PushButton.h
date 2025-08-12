#include <Arduino.h>
#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

typedef std::function<void()> ButtonPressedFn;

class PushButton
{
public:
    bool state = false;
    void init(ButtonPressedFn buttonFn, uint8_t pin);
    void toggle();
    void wasPushed();

private:
    ButtonPressedFn buttonPressedFn;
    u_int8_t buttonPin;
    bool lastButtonState = HIGH;
};

#endif