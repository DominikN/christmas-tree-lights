#include <AsyncElegantOTA.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Husarnet.h>
#include <WiFi.h>
#include <NeoPixelBus.h>

#include "LED_scheme.h"

#define HTTP_PORT 8080

#if __has_include("credentials.h")
#include "credentials.h"
#endif

// For GitHub Actions OTA deploment

// WiFi credentials
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

// Husarnet credentials
const char *husarnetJoinCode = HUSARNET_JOINCODE;  // find at app.husarnet.com
const char *hostName = "pixel-led-chain";
const char *dashboardURL = "default";

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(NUMPIXELS, PIN);

int j = 0;

uint8_t modeRGB = 0;

uint8_t rgb[3];

AsyncWebServer server(HTTP_PORT);

void setup(void) {
  // ===============================================
  // Wi-Fi, OTA and Husarnet VPN configuration
  // ===============================================

  // remap default Serial (used by Husarnet logs)
  Serial.begin(115200, SERIAL_8N1, 16, 17);  // from P3 & P1 to P16 & P17
  Serial1.begin(115200, SERIAL_8N1, 3,
                1);  // remap Serial1 from P9 & P10 to P3 & P1

  Serial1.println("\r\n**************************************");
  Serial1.println("Christmas Tree Lights");
  Serial1.println("**************************************\r\n");

  // Init Wi-Fi
  Serial1.printf("📻 1. Connecting to: %s Wi-Fi network ", ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    static int cnt = 0;
    delay(500);
    Serial1.print(".");
    cnt++;
    if (cnt > 10) {
      ESP.restart();
    }
  }

  Serial1.println(" done\r\n");

  // Init Husarnet P2P VPN service
  Serial1.printf("⌛ 2. Waiting for Husarnet to be ready ");

  Husarnet.selfHostedSetup(dashboardURL);
  Husarnet.join(husarnetJoinCode, hostName);
  Husarnet.start();

  // Before Husarnet is ready peer list contains:
  // master (0000:0000:0000:0000:0000:0000:0000:0001)
  const uint8_t addr_comp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  bool husarnetReady = 0;
  while (husarnetReady == 0) {
    Serial1.print(".");
    for (auto const &host : Husarnet.listPeers()) {
      if (host.first == addr_comp) {
        ;
      } else {
        husarnetReady = 1;
      }
    }
    delay(1000);
  }

  Serial1.println(" done\r\n");

  // define HTTP API for remote reset
  server.on("/reset", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Reseting ESP32 after 1s ...");
    Serial1.println("Software reset on POST request");
    delay(1000);
    ESP.restart();
  });

  // Init OTA webserver (available under /update path)
  AsyncElegantOTA.begin(&server);
  server.begin();

  // ===============================================
  // PLACE YOUR APPLICATION CODE BELOW
  // ===============================================

  strip.Begin();
  strip.Show();

  // Example webserver hosting table with known Husarnet Hosts
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "hello");
  });

  // Send a GET request to <IP>/sensor/<number>/action/<action>
  server.on("^\\/mode\\=([0-9]+)$", HTTP_GET, [](AsyncWebServerRequest *request) {
    String mode = request->pathArg(0);
    request->send(200, "text/plain", "Hello, mode: " + mode);
    Serial1.print("Hello, mode: " + mode + "\r\n");

    modeRGB = mode.toInt();
  });

  // Send a GET request to <IP>/sensor/<number>/action/<action>
  server.on("^\\/color\\=([a-z]+)$", HTTP_GET, [](AsyncWebServerRequest *request) {
    String color = request->pathArg(0);
    request->send(200, "text/plain", "Hello, color: " + color);
    Serial1.print("Hello, color: " + color + "\r\n");

    modeRGB = 5;

    if(color == "yellow") {
      rgb[0] = 255;
      rgb[1] = 255;
      rgb[2] = 0;
    }

    if(color == "red") {
      rgb[0] = 255;
      rgb[1] = 0;
      rgb[2] = 0;
    }

    if(color == "green") {
      rgb[0] = 0;
      rgb[1] = 255;
      rgb[2] = 0;
    }
  });

  Serial1.println("🚀 HTTP server started\r\n");
  Serial1.printf("Visit:\r\nhttp://%s:%d/\r\n\r\n", hostName, HTTP_PORT);

  Serial1.printf("Known hosts:\r\n");
  for (auto const &host : Husarnet.listPeers()) {
    Serial1.printf("%s (%s)\r\n", host.second.c_str(),
                   host.first.toString().c_str());
  }
}

void loop(void) {
  switch (modeRGB) {
    case 0:
      rainbow(j++);
      break;
    case 1:
      white_shine(j++);
      break;
    case 2:
      red_shine(j++);
      break;
    case 3:
      led_white();
      break;
    case 4:
      led_off();
      break;
    case 5:
      led_rgb(rgb[0], rgb[1], rgb[2]);
      break;
    default:
      rainbow(j++);
      break;
  }
  if (j >= NUMPIXELS) {
    j = 0;
  }
}