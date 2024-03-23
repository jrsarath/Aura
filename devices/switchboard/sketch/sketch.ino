#include <WiFi.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

float firmware_version = 1.0;
const char* ssid = "Aura-IOT";
const char* password = "9836321824";
String hostname = "Aura-Control#01";
IPAddress local_IP(192, 168, 0, 202);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(100);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.setHostname(hostname.c_str());
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRootRoute);
  server.on("/temperature", HTTP_GET, handleTemperatureRoute);
  server.on("/humidity", HTTP_GET, handleHumidityRoute);
  server.on("/aqi", HTTP_GET, handleAQIRoute);
  server.on("/admin", HTTP_GET, handleAdminRoute);
  server.onNotFound(notFound);

  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {

}