#include <WiFi.h>
#include <WebServer.h>

#define RELAY_PIN 0
#define BUTTON_PIN 1
#define WIFI_SSID "Athena"
#define WIFI_PASS "washington"

WebServer server(80);
bool relayState = false;

// Button debounce
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

void toggleRelay()
{
  relayState = !relayState;
  digitalWrite(RELAY_PIN, relayState);
  Serial.println(relayState ? "Relay ON" : "Relay OFF");
}

void handleRoot()
{
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>ESP32-C3 Relay</title>
      <style>
        body {
          font-family: Arial, sans-serif;
          display: flex;
          flex-direction: column;
          align-items: center;
          justify-content: center;
          height: 100vh;
          margin: 0;
          background-color: #f8f9fa;
        }
        h1 {
          color: #343a40;
          margin-bottom: 2rem;
        }
        .btn {
          display: inline-block;
          font-weight: 400;
          color: #fff;
          background-color: #007bff;
          border: 1px solid #007bff;
          padding: 12px 24px;
          font-size: 2rem;
          border-radius: 0.3rem;
          cursor: pointer;
          text-decoration: none;
          transition: background-color 0.15s;
        }
        .btn:hover {
          background-color: #0056b3;
        }
        .btn[disabled] {
          cursor: not-allowed;
          opacity: 0.65;
          pointer-events: none;
        }
        .status {
          font-size: 1.2rem;
          margin-bottom: 20px;
          color: #555;
        }
      </style>
    </head>
    <body>
      <h1>ESP32-C3 Relay Control</h1>
      <form action="/toggle" method="POST">
        <button class="btn" type="submit" disabled id="toggler">%STATE%</button>
      </form>
      <script>
        const poolSeconds = 1;
        const btnDelaySeconds = 2;

        const schedulePoolEvent = () => {
          window.setInterval(() => {
            fetch('/status')
              .then(response => response.json())
              .then(data => {
                document.getElementById('toggler').innerText = data.state;
              });
          }, poolSeconds * 1000);
        }

        const setButtonClickEvent = () => {
          window.setTimeout(() => {
            document
              .getElementById('toggler')
              .removeAttribute('disabled');
          }, btnDelaySeconds * 1000)
        }

        window.addEventListener('load', () => {
            schedulePoolEvent();
            setButtonClickEvent();
        });
      </script>
    </body>
    </html>
  )rawliteral";

  html.replace("%STATE%", relayState ? "ON" : "OFF");
  server.send(200, "text/html", html);
}

void handleToggle()
{
  toggleRelay();
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleStatus()
{
  server.send(200, "application/json", relayState ? "{\"state\":\"ON\"}" : "{\"state\":\"OFF\"}");
}

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, relayState);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Fix low quality board
  // Source: https://forum.arduino.cc/t/no-wifi-connect-with-esp32-c3-super-mini/1324046/14
  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", HTTP_POST, handleToggle);
  server.on("/status", HTTP_GET, handleStatus);

  server.begin();
}

void loop()
{
  server.handleClient();

  int reading = digitalRead(BUTTON_PIN);
  bool btnPressed = reading == LOW;
  bool stateChanged = lastButtonState == HIGH;
  bool minBtnDelay = (millis() - lastDebounceTime) > debounceDelay;

  if (btnPressed && stateChanged && minBtnDelay)
  {
    handleToggle();
    lastDebounceTime = millis();
  }

  lastButtonState = reading;
}
