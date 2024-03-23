#include <WiFi.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <unordered_map>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

float firmware_version = 1.0;
const char* ssid = "Aura-IOT";
const char* password = "9836321824";
String hostname = "Aura Control-01";
IPAddress local_IP(192, 168, 0, 202);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
AsyncWebServer server(80);

std::unordered_map<int, int> pins = {{1, 13}, {2, 14}};

void setup() {
  Serial.begin(115200);
  delay(100);

  setupPins();
  setupWiFi();
  setupServer();
}

void loop() {
}
void setupPins() {
  pinMode(LED_BUILTIN, OUTPUT);
  for (const auto& entry : pins) {
    pinMode(entry.second, OUTPUT);
  }
}
void setupWiFi() {
  WiFi.config(local_IP, gateway, subnet);
  WiFi.setHostname(hostname.c_str());
  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
}
void setupServer() {
  server.on("/control", HTTP_POST, handleControlRoute);
  server.onNotFound(notFound);
  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(LED_BUILTIN, HIGH);
}

void handleControlRoute(AsyncWebServerRequest *request) {
  String response;
  JsonDocument doc;
  int switchNumber = -1;

  int paramsLength = request->params();
  for(int i = 0; i < paramsLength; i++) {
    AsyncWebParameter* p = request->getParam(i);
    if (p->name() == "switch") {
      switchNumber = p->value().toInt();
      break;
    }
  }

  if (switchNumber != -1) {
    if (pins.find(switchNumber) != pins.end()) {
      int pin = pins[switchNumber];
      Serial.println(pin);
      String action = request->getParam("action")->value();
      Serial.println(action);
      if (action == "on") {
        digitalWrite(pin, HIGH);
      } else if (action == "off") {
        digitalWrite(pin, LOW);
      }
      doc["code"] = 200;
      doc["message"] = "Switch control completed";
    } else {
      doc["code"] = 400;
      doc["message"] = "Invalid switch number";
    }
  } else {
    doc["code"] = 400;
    doc["message"] = "Switch parameter not provided";
  }

  serializeJson(doc, response);
  request->send(200, "application/json; charset=utf8", response);
}
void notFound(AsyncWebServerRequest *request){
  String response;
  JsonDocument doc;
  doc["code"] = 404;
  doc["message"] = "route not found";
  serializeJson(doc, response);
  request->send(404, "application/json; charset=utf8", response);
}