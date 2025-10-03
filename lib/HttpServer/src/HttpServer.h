#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "types.h"

class HttpServer
{
public:
    HttpServer();
    void init(RelayTogglerFn toggleFn,
              RelayOnFn onFn,
              RelayOffFn offFn,
              RelayStateFn stateFn);

private:
    AsyncWebServer webServer;
    RelayTogglerFn relayTogglerFn;
    RelayOnFn relayOnFn;
    RelayOffFn relayOffFn;
    RelayStateFn relayStateFn;
    void handleRoot(AsyncWebServerRequest *request);
    void handleStatus(AsyncWebServerRequest *request);
    void toggleRelay(AsyncWebServerRequest *request);
    void turnOnRelay(AsyncWebServerRequest *request);
    void turnOffRelay(AsyncWebServerRequest *request);
};

#endif