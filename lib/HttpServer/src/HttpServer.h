#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "types.h"


typedef std::function<bool()> RelayStateFn;

class HttpServer
{
public:
    HttpServer();
    void init(RelayTogglerFn toggleFn, RelayStateFn stateFn);

private:
    AsyncWebServer webServer;
    RelayTogglerFn relayTogglerFn;
    RelayStateFn relayStateFn;
    void handleRoot(AsyncWebServerRequest* request);
    void handleStatus(AsyncWebServerRequest* request);
    void toggleRelay(AsyncWebServerRequest* request);
};

#endif