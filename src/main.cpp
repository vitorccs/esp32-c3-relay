#include <Arduino.h>
#include <NoDelay.h>
#include <HttpServer.h>
#include <WifiHandler.h>
#include <PushButton.h>
#include "types.h"

#define RELAY_PIN 0
#define BUTTON_PIN 1
#define LED_PIN 2
#define WIFI_SSID "Athena"
#define WIFI_PWD "washington"

HttpServer httpServer;
WifiHandler wifiHandler;
PushButton pushButton;
noDelay wifiTimer;
noDelay btnBounceTimer;


void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, pushButton.state);
  digitalWrite(LED_PIN, pushButton.state);

  RelayTogglerFn relayToggler = [&]
  {
    pushButton.toggle();
    digitalWrite(RELAY_PIN, pushButton.state);
    digitalWrite(LED_PIN, pushButton.state);
    Serial.println(pushButton.state ? "Relay ON" : "Relay OFF");
  };

  RelayStateFn getRelayState = [&]
  {
    return pushButton.state;
  };

  pushButton.init(relayToggler, BUTTON_PIN);

  wifiHandler.connect(WIFI_SSID, WIFI_PWD);

  httpServer.init(relayToggler, getRelayState);

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
