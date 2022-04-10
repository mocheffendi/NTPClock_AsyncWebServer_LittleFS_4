
// Create an Event Source on /events
AsyncEventSource events("/events");

// Replaces placeholder with LED state value
String processor(const String& var) {
  if (var == "STATE") {
    if (digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    return ledState;
  }
  return String();
}

String state(const String& var) {
  uptime::calculateUptime();
  uphari = String(uptime::getDays());
  upjam = String(uptime::getHours());
  upmenit = String(uptime::getMinutes());
  updetik = String(uptime::getSeconds());
  upmilidetik = String(uptime::getMilliseconds());
  //Serial.println("\tUptime : " +uphari+":"+upjam+":"+upmenit+":"+updetik+":"+upmilidetik);
  if (var == "CHIPID") {
    String chipid = FlashChipID;
    //Serial.println(chipid);
    return chipid;
  }
  if (var == "CHIPFREQ") {
    String chipfreq = CPUFreqMhz;
    return chipfreq;
  }
  if (var == "CHIPVCC") {
    String chipvcc = VCC;
    return chipvcc;
  }
  if (var == "HEAPUSES") {
    int heapuse = 81920 - ESP.getFreeHeap();
    String heapuses = String(heapuse);
    return heapuses;
  }
  if (var == "FREEHEAP") {

    String freeheap = String(ESP.getFreeHeap());
    return freeheap;
  }
  if (var == "SKETCHUSE") {
    String sketchuse = String(ESP.getSketchSize());
    return sketchuse;
  }
  if (var == "SSIDNAME") {
    String ssidname = WiFi.SSID();
    return ssidname;
  }
  if (var == "IPADDRESS") {
    String ipaddress = LocalIP;
    return ipaddress;
  }
  if (var == "GATEWAY") {
    String gateway = GateWay;
    return gateway;
  }
  if (var == "MASK") {
    String mask = SubnetMask;
    return mask;
  }
  if (var == "DNS") {
    String dnsip = DNSIP;
    return dnsip;
  }
  if (var == "MAC") {
    String macaddress = MACAddressHW;
    return macaddress;
  }
  if (var == "UPHARI") {
    //Serial.println(uphari);
    return String(uphari);
  }
  if (var == "UPJAM") {
    //Serial.println(upjam);
    return String(upjam);
  }
  if (var == "UPMENIT") {
    //Serial.println(upmenit);
    return String(upmenit);
  }
  if (var == "UPDETIK") {
    //Serial.println(updetik);
    return String(updetik);
  }
  if (var == "UPMILIDETIK") {
    //Serial.println(upmilidetik);
    return String(upmilidetik);
  }
  /*
    else if(var == "HUMIDITY"){
    return String(humidity);
    }
    else if(var == "PRESSURE"){
    return String(pressure);
    }
  */
  return String();
}

void asyncwebInit() {
  if (WiFi.status() == WL_CONNECTED) {
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(LittleFS, "/index.html", "text/html", false, state);
    });
    server.serveStatic("/", LittleFS, "/");

    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
      digitalWrite(ledPin, HIGH);
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    });

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
      digitalWrite(ledPin, LOW);
      request->send(LittleFS, "/index.html", "text/html", false, processor);
    });

    // Web Server wifimanager URL
    server.on("/wifimanager", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(LittleFS, "/index.html", "text/html", false, state);
    });

    server.on("/wifimanager", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            //Serial.print("SSID set to: ");
            //Serial.println(ssid);
            // Write file to save value
            writeFile(LittleFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            //Serial.print("Password set to: ");
            //Serial.println(pass);
            // Write file to save value
            writeFile(LittleFS, passPath, pass.c_str());
          }

          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(LittleFS, "/index.html", "text/html", false, state);
      newDelay(3000);
      ESP.restart();
    });

    // Web Server jammanager URL
    server.on("/jammanager", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(LittleFS, "/index.html", "text/html", false, state);
    });

    server.on("/jammanager", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          if (p->name() == PARAM_JAMBESAR) {
            jambesar = p->value().c_str();
            Serial.print("PARAM_JAMBESAR set to: ");
            Serial.println(jambesar);
            Disp.clear();
            // Set Brightness
            //Disp.setBrightness(brightness.toInt());
            // Write file to save value
            writeFile(LittleFS, jambesarPath, jambesar.c_str());
          }

          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      //request->send(200, "text/plain", "Done." );
      request->send(LittleFS, "/", "text/html", false, processor);
      //newDelay(3000);
      //ESP.restart();
    });

    // Web Server ntp URL
    server.on("/ntp", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(LittleFS, "/index.html", "text/html", false, state);
    });

    server.on("/ntp", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          if (p->name() == PARAM_INTERVAL_NTP) {
            intervalntp = p->value().c_str();
            Serial.print("INTERVAL NTP set to: ");
            Serial.println(intervalntp);
            // Write file to save value
            writeFile(LittleFS, intervalntpPath, intervalntp.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_NTP_POOL) {
            Serial.println("\t P Value : " + String(p->value().c_str()));
            if (p->value().c_str() != "") {
              ntppool = p->value().c_str();
              Serial.print("NTPPool set to: ");
              Serial.println(ntppool);
              // Write file to save value
              writeFile(LittleFS, ntppoolPath, ntppool.c_str());
            }
          }

          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(LittleFS, "/index.html", "text/html", false, state);
      //newDelay(3000);
      //ESP.restart();
    });

    // Web Server weather URL
    server.on("/weather", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(LittleFS, "/index.html", "text/html", false, state);
    });

    server.on("/weather", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          if (p->name() == PARAM_INTERVAL_WEATHER_UPDATE) {
            intervalweatherupdate = p->value().c_str();
            //Serial.print("PARAM_INTERVAL_WEATHER_UPDATE set to: ");
            //Serial.println(intervalweatherupdate);
            // Write file to save value
            writeFile(LittleFS, intervalweatherupdatePath, intervalweatherupdate.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_OPENWEATHERMAPAPIKEY) {
            openweathermapapikey = p->value().c_str();
            //Serial.print("PARAM_OPENWEATHERMAPAPIKEY set to: ");
            //Serial.println(openweathermapapikey);
            // Write file to save value
            writeFile(LittleFS, openweathermapapikeyPath, openweathermapapikey.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_CITY) {
            city = p->value().c_str();
            //Serial.print("PARAM_CITY set to: ");
            //Serial.println(city);
            // Write file to save value
            writeFile(LittleFS, cityPath, city.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_WEATHER_HOSTNAME) {
            weatherhostname = p->value().c_str();
            //Serial.print("PARAM_WEATHER_HOSTNAME set to: ");
            //Serial.println(weatherhostname);
            // Write file to save value
            writeFile(LittleFS, weatherhostnamePath, weatherhostname.c_str());
          }

          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      //request->send(200, "text/plain", "Done." );
      request->send(LittleFS, "/index.html", "text/html", false, state);
      //newDelay(3000);
      //ESP.restart();
    });

    // Web Server brightness URL
    server.on("/brightness", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(LittleFS, "/index.html", "text/html", false, state);
    });

    server.on("/brightness", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          if (p->name() == PARAM_BRIGHTNESS) {
            brightness = p->value().c_str();
            //Serial.print("PARAM_BRIGHTNESS set to: ");
            //Serial.println(brightness);
            // Set Brightness
            Disp.setBrightness(brightness.toInt());
            // Write file to save value
            writeFile(LittleFS, brightnessPath, brightness.c_str());
          }

          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      //request->send(200, "text/plain", "Done." );
      request->send(LittleFS, "/index.html", "text/html", false, state);
      //newDelay(3000);
      //ESP.restart();
    });

    // Web Server runningtext URL
    server.on("/runningtext", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(LittleFS, "/index.html", "text/html", false, state);
    });

    server.on("/runningtext", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          if (p->name() == PARAM_RUNNINGTEXT) {
            runningtext = p->value().c_str();
            //Serial.print("PARAM_RUNNINGTEXT set to: ");
            //Serial.println(runningtext);
            // Write file to save value
            Disp.clear();
            tampil = 1;
            writeFile(LittleFS, runningtextPath, runningtext.c_str());
          }

          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      //request->send(200, "text/plain", "Done." );
      request->send(LittleFS, "/index.html", "text/html", false, state);
      //newDelay(3000);
      //ESP.restart();
    });

    // Handle Web Server Events
    /*
      events.onConnect([](AsyncEventSourceClient * client) {
      if (client->lastId()) {
        Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
      }
      // send event with message "hello!", id current millis
      // and set reconnect delay to 1 second
      client->send("hello!", NULL, millis(), 1000);
      });

      server.addHandler(&events);
    */
    AsyncElegantOTA.begin(&server);    // Start ElegantOTA
    server.begin();
    Serial.println("[INFO] Server Begin");
    Serial.println("[INFO] Server OTA Begin");
  }
}

void UpTime() {
  uptime::calculateUptime();
  uphari = String(uptime::getDays());
  upjam = String(uptime::getHours());
  upmenit = String(uptime::getMinutes());
  updetik = String(uptime::getSeconds());
  upmilidetik = String(uptime::getMilliseconds());
  //Serial.println("\tUptime : " +uphari+":"+upjam+":"+upmenit+":"+updetik+":"+upmilidetik);

  // Send Events to the Web Server
  events.send("ping", NULL, millis());
  events.send(String(uphari).c_str(), "uphari", millis());
  events.send(String(upjam).c_str(), "upjam", millis());
  events.send(String(upmenit).c_str(), "upmenit", millis());
  events.send(String(updetik).c_str(), "updetik", millis());
  events.send(String(upmilidetik).c_str(), "upmilidetik", millis());
}
