#include <PushButton.h>

bool relayState = false;

void PushButton::init(RelayTogglerFn toggleFn, uint8_t btnPin)
{
  relayTogglerFn = toggleFn;
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
    relayTogglerFn();
  }

  lastButtonState = reading;
}