#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H
#include <WifiHandler.h>

void WifiHandler::connect(const char *ssid,
                          const char *pwd)
{
    WiFi.begin(ssid, pwd);

    // Fix low quality board
    // Source: https://forum.arduino.cc/t/no-wifi-connect-with-esp32-c3-super-mini/1324046/14
    WiFi.setTxPower(WIFI_POWER_8_5dBm);

    // Prevents Power Save Mode
    WiFi.setSleep(false);

    Serial.print("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    debug(WiFi, ssid);
}

void WifiHandler::debug(WiFiClass WiFi,
                        const char *ssid)
{
    Serial.println("");
    Serial.print("Wi-Fi connected at ");
    Serial.println(ssid);
    Serial.print("http://");
    Serial.println(WiFi.localIP());
}

void WifiHandler::reconnect()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    unsigned long startTime = millis();

    Serial.println("Reconnecting to Wi-Fi...");

    WiFi.disconnect(false, false);
    WiFi.reconnect();

    while (WiFi.status() != WL_CONNECTED && millis() - startTime < reconnectTimeout)
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nWi-Fi reconnected successfully!");
    }
    else
    {
        Serial.println("\nFailed to reconnect. Restarting ESP32...");
        ESP.restart();
    }
}

#endif