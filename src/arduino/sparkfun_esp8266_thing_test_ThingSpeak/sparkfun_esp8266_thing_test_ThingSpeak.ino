/**
 * IoT Kit - Temperature and Humidity Logger
 * Author: Shawn Hymel (SparkFun Electronics)
 * Date: October 30, 2016
 * 
 * Log temperature and humidity data to a channel on
 * thingspeak.com once every 20 seconds.
 * 
 * Connections:
 *   Thing Dev |  RHT03
 *  -----------|---------
 *      3V3    | 1 (VDD) 
 *        4    | 2 (DATA)
 *      GND    | 4 (GND)
 *      
 * Development environment specifics:
 *  Arduino IDE v1.6.5
 *  Distributed as-is; no warranty is given.  
 */

#include <ESP8266WiFi.h>
//#include <SparkFun_RHT03.h>
#include "ThingSpeak.h"

// WiFi and Channel parameters
const char WIFI_SSID[] = "FREE_PUBLIC_WIFI";
const char WIFI_PSK[] = "justkidding!1602C";
unsigned long CHANNEL_ID = 1593038;
const char * WRITE_API_KEY = "ZHNDRAFXFYL4LNVL";

// Pin definitions
//const int RHT03_DATA_PIN = 4;
const int LED_PIN = 5;

// Global variables
WiFiClient client;

void setup() {

  // Set up LED for debugging
  pinMode(LED_PIN, OUTPUT);

  // Connect to WiFi
  connectWiFi();

  // Initialize connection to ThingSpeak
  ThingSpeak.begin(client);

  // Call rht.begin() to initialize the sensor and our data pin
  //rht.begin(RHT03_DATA_PIN);
}

void loop() {

  // Flash LED to show that we're sampling
  digitalWrite(LED_PIN, LOW);

  // If successful, the update() function will return 1.
  if (1 == 1)
  {

    // Write the values to our ThingSpeak channel
    ThingSpeak.setField(1, 10);
    ThingSpeak.setField(2, 100);
    ThingSpeak.setField(3, 1000);
    ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);
  }
  else
  {

    // If the update failed, try delaying for some time
    delay(100);
  }

  // Turn LED off when we've posted the data
  digitalWrite(LED_PIN, HIGH);

  // ThingSpeak will only accept updates every 15 seconds
  delay(15000);
}

// Attempt to connect to WiFi
void connectWiFi() {

  byte led_status = 0;

  // Set WiFi mode to station (client)
  WiFi.mode(WIFI_STA);

  // Initiate connection with SSID and PSK
  String hostname_str = "ESP-host-" + WiFi.macAddress();
  //WiFi.hostname(hostname_str);
  WiFi.begin(WIFI_SSID, WIFI_PSK);

  // Blink LED while we wait for WiFi connection
  while ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite(LED_PIN, led_status);
    led_status ^= 0x01;
    delay(250);
  }

  // Turn LED off when we are connected
  digitalWrite(LED_PIN, HIGH);
}
