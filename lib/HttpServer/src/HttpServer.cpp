#include <HttpServer.h>

HttpServer::HttpServer() : webServer(80)
{
  webServer.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) { 
    handleRoot(request);
  });

  webServer.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
    handleStatus(request);
  });

  webServer.on("/toggle", HTTP_POST, [this](AsyncWebServerRequest *request) { 
    toggleRelay(request); 
  });

  webServer.on("/on", HTTP_POST, [this](AsyncWebServerRequest *request) { 
    turnOnRelay(request); 
  });

  webServer.on("/off", HTTP_POST, [this](AsyncWebServerRequest *request) { 
    turnOffRelay(request); 
  });
}

void HttpServer::init(RelayTogglerFn toggleFn,
                      RelayOnFn onFn,
                      RelayOffFn offFn,
                      RelayStateFn stateFn)
{
  relayTogglerFn = toggleFn;
  relayOnFn = onFn;
  relayOffFn = offFn;
  relayStateFn = stateFn;

  webServer.begin();
}

void HttpServer::handleRoot(AsyncWebServerRequest *request)
{
  String indexHtml = R"rawliteral(
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
          display: flex;
          justify-content: center;
          align-items: center;
          font-weight: 500;
          color: #fff;
          background-color: #007bff;
          border: 1px solid #007bff;
          padding: 12px 24px;
          font-size: 2rem;
          border-radius: 0.3rem;
          cursor: pointer;
          text-decoration: none;
          box-shadow: 3px 3px 3px #ccc;
          transition: background-color 0.15s;
        }
        .btn:hover {
          background-color: #0056b3;
        }
        .btn.state-off {
          color: #666;
          background-color: #bbb;
          border: 1px solid #bbb;
        }  
        .btn.state-off:hover {
          background-color: #aaa;
        }
        .btn#toggler {
          min-width: 150px;
          height: 65px;
        }
        
        .btn[disabled] {
          cursor: not-allowed;
          opacity: 0.65;
          pointer-events: none;
        }
        .loader {
          display: none;
          width: 34px;
          height: 34px;
          border: 5px solid #FFF;
          border-bottom-color: transparent;
          border-radius: 50%;
          box-sizing: border-box;
          animation: rotation 1s linear infinite;
        }
        @keyframes rotation {
          0% {
            transform: rotate(0deg);
          }
          100% {
            transform: rotate(360deg);
          }
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
        <button class="btn %CLASS%" type="submit" id="toggler">
          <span class="loader"></span>
          <span class="text">%STATE%</span>
        </button>
      </form>
      <script>
        const toggler = document.querySelector('#toggler');
        const togglerText = document.querySelector('#toggler .text');
        const loader = document.querySelector('.loader');
        const form = document.querySelector('form');
        const poolDelay = 1000;
        const formDelay = 500;

        const schedulePoolEvent = () => {
          window.setInterval(() => {
            fetch('/status')
              .then(response => response.json())
              .then(data => {
                if (toggler.disabled) return;
                const relayState = data.state;
                const isTurnedOff = relayState === 'OFF';
                togglerText.innerText = relayState;
                toggler.classList.toggle('state-off', isTurnedOff)
              });
          }, poolDelay);
        }

        form.addEventListener("submit", function (e) {
          e.preventDefault();
          loader.style.display = 'block';
          togglerText.innerText = '';
          toggler.disabled = true;

          window.setTimeout(() => { 
            e.target.submit(); 
          }, formDelay);
        });

        window.addEventListener('load', () => {
          schedulePoolEvent();
        });
      </script>
    </body>
    </html>
  )rawliteral";

  indexHtml.replace("%CLASS%", relayStateFn() ? "" : "state-off");
  indexHtml.replace("%STATE%", relayStateFn() ? "ON" : "OFF");
  request->send(200, "text/html", indexHtml);
}

void HttpServer::toggleRelay(AsyncWebServerRequest *request)
{
  relayTogglerFn();
  request->redirect("/");
}

void HttpServer::turnOnRelay(AsyncWebServerRequest *request)
{
  relayOnFn();
  request->redirect("/");
}

void HttpServer::turnOffRelay(AsyncWebServerRequest *request)
{
  relayOffFn();
  request->redirect("/");
}

void HttpServer::handleStatus(AsyncWebServerRequest *request)
{
  const String state = relayStateFn() ? "ON" : "OFF";
  request->send(200, "application/json", "{\"state\":\"" + state + "\"}");
}
