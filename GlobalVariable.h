ADC_MODE(ADC_VCC); //Add the following line to the top of your sketch to use getVcc:

#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <Arduino_JSON.h>
#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//#include <WiFiClient.h>
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWiFiManager.h>

//Include the SSL client
#include <WiFiClientSecure.h>
//#include <WiFiClientSecureBearSSL.h>

#include "uptime.h"
String uphari;
String upjam;
String upmenit;
String updetik;
String upmilidetik;
char* Message;

//for LED status
#include <Ticker.h>
Ticker ticker;
DNSServer dns;

char Suhu[3];
//String openWeatherMapApiKey = "377940e26eb038f489fbd04274a79204";
//String city = "Surabaya";
String countryCode = "IDN";
String jsonBuffer;

HTTPClient http;
WiFiClientSecure client;
JSONVar myObject;

int temperature = 0;
int humidity = 0;

String epochstr;
String tempStr;
String TempStr;
String HumiStr;
double temp;
double humidityD;

bool tampilsuhu;

SimpleTimer timer;
int TimerNTP;
int TimerJam;
int TimerTanggal;
int TimerWeatherUpdate;
int TimerBacaRtc;

//flag for saving data
bool shouldSaveConfig = false;

IPAddress deviceIP;

String FreeHeap;
String SketchSize;
String FlashChipID;
String CPUFreqMhz;
String VCC;

String LocalIP;
String SubnetMask;
String GateWay;
String DNSIP;
String MACAddressHW;

uint8_t tampil;
static boolean huruf;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";

const char* PARAM_INTERVAL_NTP = "intervalntp";
const char* PARAM_NTP_POOL = "ntpPool";

const char* PARAM_INTERVAL_WEATHER_UPDATE = "IntervalWeatherUpdate";
const char* PARAM_OPENWEATHERMAPAPIKEY = "openWeatherMapApiKey";
const char* PARAM_CITY = "City";
const char* PARAM_WEATHER_HOSTNAME = "weatherHostName";

const char* PARAM_BRIGHTNESS = "Brightness";

const char* PARAM_JAMBESAR = "JamBesar";

const char* PARAM_RUNNINGTEXT = "RunningText";

//Variables to save values from HTML form
String ssid;
String pass;

String intervalntp;
String ntppool;

String intervalweatherupdate;
String openweathermapapikey;
String city;
String weatherhostname;

String brightness;

String jambesar;

String runningtext;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";

// File paths to save input values permanently
const char* intervalntpPath = "/intntp.txt";
const char* ntppoolPath = "/ntppool.txt";

const char* intervalweatherupdatePath = "/iwu.txt";
const char* openweathermapapikeyPath = "/owmak.txt";
const char* cityPath = "/c.txt";
const char* weatherhostnamePath = "/whn.txt";

const char* brightnessPath = "/b.txt";

const char* jambesarPath = "/jb.txt";

const char* runningtextPath = "/rt.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Set LED GPIO
const int ledPin = 2;

// Stores LED state
String ledState;

String LocalIPStr;
