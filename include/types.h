#include <Arduino.h>

typedef std::function<bool()> RelayStateFn;
typedef std::function<void()> RelayTogglerFn;
typedef std::function<void()> RelayOnFn;
typedef std::function<void()> RelayOffFn;