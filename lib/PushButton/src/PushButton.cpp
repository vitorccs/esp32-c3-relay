#include <Arduino.h>
#include <PushButton.h>

bool relayState = false;

void PushButton::init(ButtonPressedFn buttonFn, uint8_t btnPin)
{
  buttonPressedFn = buttonFn;
  buttonPin = btnPin;

  pinMode(buttonPin, INPUT_PULLUP);
}

void PushButton::toggle()
{
  state = !state;
}

void PushButton::wasPushed()
{
  int reading = digitalRead(buttonPin);
  bool btnPressed = reading == LOW;
  bool stateChanged = lastButtonState == HIGH;

  if (btnPressed && stateChanged)
  {
    buttonPressedFn();
  }

  lastButtonState = reading;
}