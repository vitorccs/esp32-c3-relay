# ESP32-C3 LED Relay
A simple ESP32-C3 project to control a LED strip via a web interface and a physical push button. The web page reflects the current LED state in real time.

### Turned Off
<img width="400" src="https://github.com/user-attachments/assets/70e70242-21c3-4916-af86-39528947e231" />
<img width="389" src="https://github.com/user-attachments/assets/7cdb0d37-6a4f-467d-b633-77403bfb5044" />

### Turned On
<img width="400" src="https://github.com/user-attachments/assets/350cad7f-53e1-4bb9-a48a-dd487f9a22c7" />
<img width="389" src="https://github.com/user-attachments/assets/1387a579-edc2-4085-a932-e9c9b3a698da" />

### The push button
<img width="400" src="https://github.com/user-attachments/assets/efb497c9-0103-4b13-a689-5130bdc15a99" />


## Simple API
Additionally, the LED can be controlled via a simple API, making it easy to integrate with home automation (e.g.: set up a cron job to turn it on and off automatically):
* `POST` `http://192.168.1.190/off`
* `POST` `http://192.168.1.190/on`

NOTE: Change `http://192.168.1.190` to your actual device IP. Assign a Static IP to your device in your home router.


## Protoboard
<img width="500" src="https://github.com/user-attachments/assets/438e24fc-e4eb-49a2-ba9b-e5497ff71c21" />


The connectors are: 12v Power Source, Push Button, 12v LED Strip.


## Schematics

**Option A) 5v LED Strip**
<img width="1849" height="900" src="https://github.com/user-attachments/assets/d9c7043b-97a2-40d5-8ab3-f44e8112831a" />

**Option B) 12v LED Strip**
<img width="2228" height="935" src="https://github.com/user-attachments/assets/c636e385-fe98-46d0-ad91-9715a980daa4" />


### Notes:
1) Gate resistor (220Ω) is optional but recommended to prevent spikes.
2) Pull-down resistor (10kΩ) between Gate and GND is optional but prevents accidental turn-on during boot.

## Components
* 01 ESP32-C3 Mini board
* 01 Push Button
* 01 Green LED
* 02 220Ω Resistors
* 01 10KΩ Resistor
* 01 N-channel MOSFET able to work with 3.3v logic (e.g.: IRFZ44N)
* 01 LED Strip (5v or 12v)
* 01 Power Supply (5v or 12v)
* 01 Mini 360 DC-DC Bulk Converter (in case the Power Supply is 12v)


## About PlatformIO IDE
Platform IO is a plugin for Microsoft Virtual Studio Code. It is a more robust IDE compared to official Arduino IDE. It also allows us to easily create our own private libraries and use a more object oriented code.

## About the code
The PINs can be customized in the `main.cpp`

```c++
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
```

## Fritzing file
* [esp32-c3-led-relay-v1.zip](https://github.com/user-attachments/files/23349078/esp32-c3-led-relay-v1.zip)
