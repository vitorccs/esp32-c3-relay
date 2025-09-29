# ESP32-C3 LED Relay
A simple ESP32-C3 project to control a LED stripe via a web interface and a physical push button. The web page reflects the current LED state in real time.

**5v LED Strip**
<img width="1853" height="903" alt="Image" src="https://github.com/user-attachments/assets/4d1807fe-e351-4c0e-bdb2-efe8b5ec5c2a" />

**12v LED Strip**
<img width="2264" height="906" alt="Image" src="https://github.com/user-attachments/assets/af03139a-c618-4731-8b2b-5001036acbd1" />

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
* [esp32-c3-led-relay-v1.zip](https://github.com/user-attachments/files/22605275/esp32-c3-led-relay-v1.zip)
