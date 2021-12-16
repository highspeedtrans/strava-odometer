#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#define DEBUG_CHANNEL 2 // none = 0, serial = 1, thingspeak = 2
#if DEBUG_CHANNEL == 2
#include <ThingSpeak.h>
#endif

unsigned long CHANNEL_ID = 1593038;
const char * WRITE_API_KEY = "ZHNDRAFXFYL4LNVL";
int miles_int; 

WiFiClient client;
ESP8266WiFiMulti WiFiMulti;

const int LED_PIN = 5;
int miles;

void setup() {
  #if DEBUG_CHANNEL == 1
  Serial.begin(9600);
  Serial.println("Starting WiFiManager...");
  #endif
  WiFiManager wifiManager;
  wifiManager.autoConnect("Strava-Odometer");
  #if DEBUG_CHANNEL == 1
  Serial.println("WiFiManager finished");
  #elif DEBUG_CHANNEL == 2
  ThingSpeak.begin(client);
  #endif
}

void loop() {
  //miles = milesRun();

  #if DEBUG_CHANNEL == 1
  //Serial.print(miles);
  //Serial.println(" miles");
  #elif DEBUG_CHANNEL == 2
  ThingSpeak.setField(1, milesRun());
  ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);
  #endif

  // poll Strava every 15min
  delay(900000);
}

int milesRun() { //connect to wifi, get miles run from strava api, disconnect from wifi
  if ((WiFiMulti.run() == WL_CONNECTED)) {    
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    if (https.begin(*client, "https://www.strava.com/api/v3/athletes/*****athlete#*****/stats?access_token=*****access token here *****")) {  // HTTPS
      int httpCode = https.GET();
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          const size_t capacity = 6*JSON_OBJECT_SIZE(5) + 3*JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(11) + 1220;
          DynamicJsonBuffer jsonBuffer(capacity);
          JsonObject& root = jsonBuffer.parseObject(https.getString());
          if (!root.success()) {
            return 0; //json parsing failed
          }
          JsonObject& all_run_totals = root["all_run_totals"];
          int meters = all_run_totals["distance"];
          return meters * 0.000621371; //to miles
        }
      } else {
        return 0; //error check httpCode
      }
      https.end();
    } else {
      return 0; //error unable to connect
    }
  }
}
