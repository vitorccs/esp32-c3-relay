#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <Arduino.h>
#include <WebServer.h>

typedef std::function<void()> RelayTogglerFn;
typedef std::function<bool()> RelayStateFn;

class HttpServer
{
public:
    HttpServer();
    void init(RelayTogglerFn toggleFn, RelayStateFn stateFn);
    void toggleRelay();
    void loop();

private:
    WebServer webServer;
    RelayTogglerFn relayTogglerFn;
    RelayStateFn relayStateFn;
    void handleRoot();

    void handleStatus();
};

#endif