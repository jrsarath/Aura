#include "DHT.h"
#include <WiFi.h>
#include <Wire.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include "Adafruit_SGP40.h"
#include <ESPAsyncWebServer.h>


float firmware_version = 1.0;
const char* ssid = "Aura-IOT";
const char* password = "9836321824";
String hostname = "Aura-SensorsNode";
IPAddress local_IP(192, 168, 0, 201);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
AsyncWebServer server(80);

#define DHTTYPE DHT22
#define DHTPIN 13
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SGP40 sgp;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(100);

  dht.begin();
  if (!sgp.begin()){
    Serial.println("SGP40 Sensor not found");
    while (1);
  }           

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

void handleRootRoute(AsyncWebServerRequest *request) {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  uint16_t aqi = sgp.measureVocIndex(temperature, humidity);
  String response;
  JsonDocument doc;
  doc["temperature"] = isnan(temperature) ? 0 : temperature;
  doc["humidity"] = isnan(humidity) ? 0 : humidity;
  doc["aqi"] = isnan(aqi) ? 0 : aqi;
  serializeJson(doc, response);
  request->send(200, "application/json; charset=utf8", response); 
}
void handleTemperatureRoute(AsyncWebServerRequest *request) {
  float temperature = dht.readTemperature();
  String response;
  JsonDocument doc;
  doc["temperature"] = isnan(temperature) ? 0 : temperature;
  serializeJson(doc, response);
  request->send(200, "application/json; charset=utf8", response); 
}
void handleHumidityRoute(AsyncWebServerRequest *request) {
  float humidity = dht.readHumidity();
  String response;
  JsonDocument doc;
  doc["humidity"] = isnan(humidity) ? 0 : humidity;
  serializeJson(doc, response);
  request->send(200, "application/json; charset=utf8", response);
}
void handleAQIRoute(AsyncWebServerRequest *request) {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  uint16_t aqi = sgp.measureVocIndex(temperature, humidity);
  String response;
  JsonDocument doc;
  doc["aqi"] = isnan(aqi) ? 0 : aqi;
  serializeJson(doc, response);
  request->send(200, "application/json; charset=utf8", response);
}
void handleAdminRoute(AsyncWebServerRequest *request){
  const char html[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
      <head>
        <title>Aura- Climate Control</title>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <style>
          html,body,div,span,applet,object,iframe,h1,h2,h3,h4,h5,h6,p,blockquote,pre,a,abbr,acronym,address,big,cite,code,del,dfn,em,img,ins,kbd,q,s,samp,small,strike,strong,sub,sup,tt,var,b,u,i,center,dl,dt,dd,ol,ul,li,fieldset,form,label,legend,table,caption,tbody,tfoot,thead,tr,th,td,article,aside,canvas,details,embed,figure,figcaption,footer,header,hgroup,menu,nav,output,ruby,section,summary,time,mark,audio,video{margin:0;padding:0;border:0;font-size:100%;vertical-align:baseline}article,aside,details,figcaption,figure,footer,header,hgroup,menu,nav,section{display:block}body{line-height:1}ol,ul{list-style:none}blockquote,q{quotes:none}blockquote:before,blockquote:after,q:before,q:after{content:"";content:none}table{border-collapse:collapse;border-spacing:0}
        </style>
        <style>
          :root{--color-primary-0:#ffffff;--color-primary-100:#dfcaff;--color-primary-200:#bc97ff;--color-primary-300:#9364fe;--color-primary-500:#5d2dfb;--color-primary-600:#4925b6;--color-primary-700:#351d76;--color-primary-800:#20133b;--color-primary-900:#000000}*{font-family:Helvetica,sans-serif;box-sizing:border-box}body{width:100%;height:100%;display:flex;position:fixed;color:var(--color-primary-500);background:var(--color-primary-0)}.app{width:100%;height:100%;display:flex;overflow:auto}.page{height:100%;width:100%;justify-content:center;align-items:center;align-content:center;display:none}.page.active{display:flex}.login-page{width:100%;height:100%;display:flex;justify-content:center;align-items:center;align-content:center}.login{width:50%;max-width:300px;display:flex;flex-direction:column}.login h3{text-align:left;font-size:22px}.login h4{text-align:left;margin-bottom:15px}.input-group{margin-bottom:10px;display:flex;flex-direction:column}.input-group label{font-size:14px;margin-bottom:5px;color:#eeecf6}.input-group input{outline:0;border:0;font-size:14px;padding:10px 15px;border-radius:10px;transition:all 0.2s linear;color:#212121;border:solid 1px #9e9e9e}.input-group input:focus{border-color:var(--color-primary-500)}.btn{border:0;outline:0;border-radius:10px;background:var(--color-primary-500);color:var(--color-primary-0);padding:10px;cursor:pointer;transition:all 0.2s linear}.btn:disabled{opacity:.5}.home{width:100%;height:100%;padding:20px;display:flex;flex-direction:column}.home .header{border-radius:10px;padding:15px;display:flex;justify-content:space-between;align-items:center;position:relative;background:var(--color-primary-500);color:var(--color-primary-0);box-shadow:0 0 10px 5px rgba(93,45,251,.2)}.home .header .header-logo{border-radius:5px;width:80px;height:40px;margin-right:20px;display:flex;align-items:center;font-size:30px;font-weight:900}.home .header .header-text h2,.home .header .header-text h3{text-align:right;font-weight:500}.home .sections{width:100%;margin-top:20px;display:flex;flex-direction:column}.home .sections .section{width:100%;margin-bottom:40px}.home .sections .section .section-header{font-size:20px;font-weight:500;margin-bottom:20px}.home .sections .section .section-content .cards{width:100%;display:flex;flex-direction:row}.home .sections .section .section-content .cards .cards-column{display:flex;flex-direction:column}.home .sections .section .section-content .cards .cards-column:first-child{width:40%;margin-right:20px}.home .sections .section .section-content .cards .cards-column:last-child{width:calc(60% - 20px);margin:-10px 0}.home .sections .section .section-content .cards .card{width:100%;height:100%;padding:15px;margin:10px 0;border-radius:10px;display:flex;flex-direction:column;align-content:center;justify-content:space-between;border:solid 1px #e0e0e0;position:relative;color:#616161}.home .sections .section .section-content .cards .card.primary{margin:0;border:solid 0 transparent;background-image:linear-gradient(to right bottom,#5d2dfb,#6f3efc,#7e4efd,#8c5dfd,#996bfe);box-shadow:0 0 10px 5px rgba(93,45,251,.2);justify-content:center}.home .sections .section .section-content .cards .card.primary .card-title{color:#eee;position:absolute;top:15px;left:15px}.home .sections .section .section-content .cards .card.primary .card-content{font-size:150px;color:var(--color-primary-0);text-align:center;display:flex;flex-direction:column}.home .sections .section .section-content .cards .card.primary .card-content span{font-size:30px;font-weight:500}.home .sections .section .section-content .cards .card .card-content{color:var(--color-primary-500);font-weight:700;font-size:60px;margin-top:10px}.home .sections .section .section-content ul{width:100%}.home .sections .section .section-content ul li{color:#616161;display:flex;flex-direction:row;justify-content:space-between;align-items:center;padding:20px;border-radius:10px;margin-bottom:15px;font-weight:500;border:solid 1px #e0e0e0}.home .sections .section .section-content ul li span:last-child{color:var(--color-primary-900)}.home .sections .section .section-content ul li a{color:#382bf0;cursor:pointer}
        </style>
      </head>
      <body>
        <div class="app">
          <div class="page active" id="login">
            <div class="login-page">
                <form class="login" id="login-form">
                    <h3>Aura</h3>
                    <h4>Climate Control</h4>
                    <div class="input-group">
                        <input required type="text" id="username" placeholder="Username" />
                    </div>
                    <div class="input-group">
                        <input
                        required
                        type="password"
                        id="password"
                        placeholder="Password"
                        />
                    </div>
                    <button class="btn" type="submit">Continue</button>
                </form>
            </div>
          </div>
          <div class="page" id="home">
            <div class="home">
              <div class="header">
                <div class="header-logo">Aura</div>
                <div class="header-text">
                  <h2>Climate Control</h2>
                  <h3>V1.0</h3>
                </div>
              </div>
              <div class="sections">
                <div class="section">
                  <h2 class="section-header">Overview</h2>
                  <div class="section-content">
                    <div class="cards">
                        <div class="cards-column">
                            <div class="card primary">
                                <p class="card-title">Temperature</p>
                                <div class="card-content" id="temperature">
                                    32
                                    <span>&deg; Celsius</span>
                                </div>
                            </div>
                        </div>
                        <div class="cards-column">
                            <div class="card">
                                <p class="card-title">Humidity</p>
                                <div class="card-content" id="humidity">90%</div>
                            </div>
                            <div class="card">
                                <p class="card-title">Air Quality</p>
                                <div class="card-content" id="aqi">120</div>
                            </div>
                        </div>
                    </div>
                  </div>
                </div>
                <div class="section">
                  <h2 class="section-header">System</h2>
                  <div class="section-content">
                    <ul>
                      <li>
                        <span>System Uptime</span>
                        <span>1.0</span>
                      </li>
                      <li>
                        <span>Current Version</span>
                        <span>%firmware_version%</span>
                      </li>
                      <li>
                        <span>Firmware Update</span>
                        <button class="btn" id="updater-btn">
                          Check for Update
                        </button>
                      </li>
                    </ul>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
        <script>
          let isAuthenticated=!1;const username="admin";const password="password";document.addEventListener("DOMContentLoaded",()=>{if(isAuthenticated){document.getElementById("login").classList.remove("active");document.getElementById("home").classList.add("active")}});setInterval(()=>{fetch("/").then((e)=>e.json()).then((result)=>{document.getElementById("temperature").innerHTML=`${
        result.temperature?.toFixed(2) || 0
      }<span>&deg; Celsius</span>`;document.getElementById("humidity").innerHTML=`${
        result.humidity?.toFixed(2) || 0
      }%`;document.getElementById("aqi").innerHTML=result.aqi?.toFixed(2)||0})},1000);document.getElementById("login-form").addEventListener("submit",(e)=>{e.preventDefault();const username_value=document.getElementById("username").value;const password_value=document.getElementById("password").value;if(username_value===username&&password_value===password){document.getElementById("login").classList.remove("active");document.getElementById("home").classList.add("active")}});document.getElementById("updater-btn").addEventListener("click",(e)=>{document.getElementById("updater-btn").disabled=!0})
        </script>
      </body>
    </html>
  )rawliteral";
  request->send(404, "text/html", html);
}
void notFound(AsyncWebServerRequest *request){
  String response;
  JsonDocument doc;
  doc["code"] = 404;
  doc["message"] = "route not found";
  serializeJson(doc, response);
  request->send(404, "application/json; charset=utf8", response);
}