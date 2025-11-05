#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H
#include <Arduino.h>
#include <WiFi.h>

class WifiHandler
{
public:
    void connect(const char *ssid, const char *pwd);
    void debug(WiFiClass WiFi, const char *ssid);
    void reconnect();
private:
    const unsigned long reconnectTimeout = 1000 * 60 * 5;
};
#endif