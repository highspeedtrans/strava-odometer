# strava-odometer
personal project to make a personal odometer using ESP8266, Strava API, and an odometer-style mechanical counter

# prototyping notes / resources
### electronics
- [Sparkfun ESP8266 Thing](https://www.sparkfun.com/products/13231) board, for cheapness, built-in wifi, Arduino community support
    - [Sparkfun tutorial](https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide)
    - needs programmer, using [Sparkfun FTDI Basic 3.3V](https://www.sparkfun.com/products/9873)
    - should've just bought [Sparkfun ESP8266 Thing DEV](https://www.sparkfun.com/products/13711) (instead of non-dev version), which has the USB-serial built in
- switched to [Sparkfun Thing Plus ESP32-S2](https://www.sparkfun.com/products/17743)
    - more flash, more power, better wifi compatibility 

### software
- [Strava API docs](https://developers.strava.com/docs/reference/)
    - [getting started](https://developers.strava.com/docs/getting-started/)
- [Sparkfun IoT Experiment Guide](https://learn.sparkfun.com/tutorials/internet-of-things-experiment-guide) with examples of ESP8266 used in client mode
- extremely barebones [Strava stats display on ESP8266](https://github.com/tadas-s/StravaDistanceDisplay) (no real documentation or anything, but very simple)
- https://stackoverflow.com/questions/57385712/how-to-access-strava-api
- frustrating saga with Wifi connection:
    - examples for connecting in client mode didn't work / were super unreliable to connect
    - 0-vote answer on [Arduino Stack Exchange post](https://arduino.stackexchange.com/a/71885/81605) contained the fix for me!
        - set a wifi hostname like `WiFi.hostname("ESP-host")`  before calling `WiFi.begin`
        - nevermind this isn't toally reliable either
    - look into router-side settings, I did fuck that up a few days ago doing DDNS stuff
        - look at a-b-g-n-ac settings
        - look at channel settings (can't use 13 / 14)

### mechanical
