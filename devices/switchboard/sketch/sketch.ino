#include <WiFi.h>
#include <Arduino.h>
#include <AsyncTCP.h>
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

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(100);

  setupWiFi();
  setupServer();
}

void loop() {
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
  // server.on("/", HTTP_GET, handleRootRoute);
  // server.on("/temperature", HTTP_GET, handleTemperatureRoute);
  // server.on("/humidity", HTTP_GET, handleHumidityRoute);
  // server.on("/aqi", HTTP_GET, handleAQIRoute);
  // server.on("/admin", HTTP_GET, handleAdminRoute);
  server.onNotFound(notFound);
  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(LED_BUILTIN, HIGH);
}
void notFound(AsyncWebServerRequest *request){
  String response;
  JsonDocument doc;
  doc["code"] = 404;
  doc["message"] = "route not found";
  serializeJson(doc, response);
  request->send(404, "application/json; charset=utf8", response);
}