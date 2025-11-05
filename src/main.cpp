#include <Arduino.h>
#include <NoDelay.h>
#include <HttpServer.h>
#include <WifiHandler.h>
#include <PushButton.h>
#include "types.h"

#define RELAY_PIN 0
#define BUTTON_PIN 1
#define LED_PIN 2
#define WIFI_SSID "MY_SSID"
#define WIFI_PWD "MY_PASSWORD"

HttpServer httpServer;
WifiHandler wifiHandler;
PushButton pushButton;
noDelay wifiTimer;
noDelay btnBounceTimer;

void updateRelayPins()
{
  digitalWrite(RELAY_PIN, pushButton.state);
  digitalWrite(LED_PIN, pushButton.state);
  Serial.println(pushButton.state ? "Relay ON" : "Relay OFF");
}

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  RelayStateFn getRelayState = [&]
  {
    return pushButton.state;
  };

  RelayTogglerFn relayToggler = [&]
  {
    pushButton.toggle();
    updateRelayPins();
  };

  RelayOnFn turnOnRelay = [&]
  {
    pushButton.turnOn();
    updateRelayPins();
  };

  RelayOnFn turnOffRelay = [&]
  {
    pushButton.turnOff();
    updateRelayPins();
  };

  updateRelayPins();

  pushButton.init(relayToggler, BUTTON_PIN);

  wifiHandler.connect(WIFI_SSID, WIFI_PWD);

  httpServer.init(relayToggler, turnOnRelay, turnOffRelay, getRelayState);

  wifiTimer.setdelay(5000);
  btnBounceTimer.setdelay(100);
}

void loop()
{
  if (btnBounceTimer.update())
  {
    pushButton.wasPushed();
  }

  if (wifiTimer.update())
  {
    wifiHandler.reconnect();
  }
}
