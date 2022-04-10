#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "NewDelay.h"
#include "GlobalVariable.h"
#include "RTCSodaqDS.h"
#include "RTC.h"
#include "DMDESP8266.h"
#include "LittleFSRW.h"
#include "OpenWeather.h"
#include "JAM.h"
#include "NTP.h"
#include "WiFiInit.h"
#include "AsyncWeb.h"

// Konversi angka agar ada nol didepannya jika dibawah 10
String Konversi(int sInput) {
  if (sInput < 10) {
    return "0" + String(sInput);
  } else {
    return String(sInput);
  }
}

void tick()
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (AsyncWiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  /*-- RTC Init Sodaq buat set epoch ke Hardware RTC DS3231 --*/
  Wire.begin();
  newDelay(500);
  rtc.begin();
  newDelay(2500);

  /*-- RTC Init Makuna --*/
  mulaiRTC();

  initLittleFS();

  // Load values saved in LittleFS
  //ssid = readFile(LittleFS, ssidPath);
  //pass = readFile(LittleFS, passPath);

  //Serial.println(ssid);
  //Serial.println(pass);

  //set led pin as output
  pinMode(BUILTIN_LED, OUTPUT);
  // start ticker with 0.5 because we start in AP mode and try to connect
  ticker.attach(0.6, tick);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  AsyncWiFiManager wifiManager(&server, &dns);
  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("NTP Clock")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  ticker.detach();
  //keep LED on
  digitalWrite(BUILTIN_LED, LOW);

  asyncwebInit();

  intervalntp = readFile(LittleFS, intervalntpPath);
  intervalweatherupdate = readFile(LittleFS, intervalweatherupdatePath);

  long intervalntpLong = intervalntp.toInt() * 60 * 1000;
  //Serial.println("\tInterval NTP : " + String(intervalntpLong));
  long intervalweatherupdateLong = intervalweatherupdate.toInt() * 60 * 1000;
  //Serial.println("\tInterval NTP : " + String(intervalweatherupdateLong));

  TimerNTP = timer.setInterval(intervalntpLong, NTPUpdate);
  TimerWeatherUpdate = timer.setInterval(intervalweatherupdateLong, ambildataWeather);

  //ESP.wdtFeed();

  // Load values saved in LittleFS
  brightness = readFile(LittleFS, brightnessPath);
  //Serial.println(brightness);

  jambesar = readFile(LittleFS, jambesarPath);
  //Serial.println(jambesar);

  ntppool = readFile(LittleFS, ntppoolPath);

  ntppool.toCharArray(ntpServerName, ntppool.length() + 1);
  //Serial.println(jambesar);
  Serial.println("\tNTP Pool: " + String(ntpServerName));
  
  runningtext = readFile(LittleFS, runningtextPath);

  if (WiFi.status() == WL_CONNECTED) {
    //Serial.println("Starting UDP");
    udp.begin(localPort);
    //Serial.print("Local port: ");
    //Serial.println(udp.localPort());

    Disp.start(); // Jalankan library DMDESP
    Disp.setBrightness(brightness.toInt()); // Tingkat kecerahan
    Disp.setFont(ElektronMart6x16); // Tentukan huruf
  }
  NTPUpdate();
  hwInit();
  BacaRTC();
  // Inisialisasi Weather di awal waktu
  bool onlineWeatherGetResult = GETOnlineWeatherData();
  LocalIPStr = LocalIP + " ";
}

void loop() {
  UpdateWaktu();
  Disp.loop();

  switch (tampil) {
    case 0 :
      TampilIP();
      break;
    case 1 :
      TampilRunningText();
      break;
    case 2 :
      if (jambesar == "1") {
        JamBesar1(0);
      }
      if (jambesar == "2") {
        JamBesar2(0);
      }
      if (jambesar == "3") {
        JamBesar3(0);
      }
      TampilInfo();
      break;
    case 3 :
      TampilTanggal();
      break;
    case 4 :
      TampilSuhu();
      break;
    case 5 :
      TampilKelembaban();
      break;
  }
  
  
  timer.run();
  //yield();
}
