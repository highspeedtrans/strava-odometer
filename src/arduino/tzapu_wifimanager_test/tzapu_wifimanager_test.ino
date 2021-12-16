#include <ThingSpeak.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

unsigned long CHANNEL_ID = 1593038;
const char * WRITE_API_KEY = "ZHNDRAFXFYL4LNVL";

WiFiClient client;

const int LED_PIN = 5;

void setup() {
  WiFiManager wifiManager;
  wifiManager.autoConnect("Strava-Odometer");

  ThingSpeak.begin(client);
}

void loop() {

  // Flash LED to show that we're sampling
  digitalWrite(LED_PIN, LOW);

  // If successful, the update() function will return 1.
  if (1 == 1)
  {

    // Write the values to our ThingSpeak channel
    ThingSpeak.setField(1, 5);
    ThingSpeak.setField(2, 50);
    ThingSpeak.setField(3, 500);
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
