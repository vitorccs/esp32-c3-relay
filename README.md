# ESP32-C3 LED Relay
A simple ESP32-C3 project to control a LED stripe via a web interface and a physical push button. The web page reflects the current LED state in real time.

**5v LED Strip**
<img width="1849" height="905" alt="esp32-c3-led-relay-v1-5v_bb" src="https://github.com/user-attachments/assets/0b5d2560-dc04-4f9d-9a21-eb9f29d4fa06" />

**12v LED Strip**
<img width="2271" height="905" alt="esp32-c3-led-relay-v1-12v_bb" src="https://github.com/user-attachments/assets/235a4b23-35d4-4837-bf80-b255f4bc1ec3" />


### Notes:
1) Gate resistor (220Ω) is optional but recommended to prevent spikes.
2) Pull-down resistor (10kΩ) between Gate and GND is optional but prevents accidental turn-on during boot.

## Components
* 01 ESP32-C3 Mini board
* 01 Push Button
* 01 220Ω Resistor
* 01 10KΩ Resistor
* 01 N-channel MOSFET able to work with 3.3v logic (e.g.: IRFZ44N)
* 01 LED Stripe 12v
* 01 12V Power Supply

## Fritzing file
* [esp32-c3-led-relay-v1-.zip](https://github.com/user-attachments/files/22629500/esp32-c3-led-relay-v1-.zip)
