#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(9600);
  delay(4000); //4 seconds
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("FREE_PUBLIC_WIFI", "justkidding!1602C");
}

void loop() {  
  Serial.print(milesRun());
  Serial.println(" miles");
  delay(900000); //wait 15 minutes
}

int milesRun() { //connect to wifi, get miles run from strava api, disconnect from wifi
  if ((WiFiMulti.run() == WL_CONNECTED)) {    
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    if (https.begin(*client, "https://www.strava.com/api/v3/athletes/5786827/stats?access_token=9034d4c72d7551eef4f150c19c4ee2a301c1cbad")) {  // HTTPS
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
