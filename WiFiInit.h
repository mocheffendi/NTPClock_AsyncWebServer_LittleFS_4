// Initialize WiFi
bool initWiFi() {
  if (ssid == "") {
    //Serial.println("Undefined SSID or IP address.");
    return false;
  }
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);

  /*
    if (!WiFi.config(localIP, gateway, subnet)){
    Serial.println("STA Failed to configure");
    return false;
    }
  */
  WiFi.begin(ssid.c_str(), pass.c_str());
  //Serial.println("Connecting to WiFi...");
  uint8_t wififlag;
  while (WiFi.status() != WL_CONNECTED) {
    newDelay(500);
    Serial.print(".");
    wififlag++;
    if (wififlag >= 30){
      return false;
    }
    
    
  }

  /*
    unsigned long currentMillis = millis();
    previousMillis = currentMillis;

    while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
    }
  */
  Serial.println(WiFi.localIP());
  return true;
}

void hwInit(){
  FreeHeap = String(ESP.getFreeHeap());
  SketchSize = String(ESP.getSketchSize());
  FlashChipID = String(ESP.getFlashChipId());
  CPUFreqMhz = String(ESP.getCpuFreqMHz());
  float vcc = ESP.getVcc() / 1000;
  VCC = String(vcc);

  LocalIP = WiFi.localIP().toString();
  SubnetMask = WiFi.subnetMask().toString();
  GateWay = WiFi.gatewayIP().toString();
  DNSIP = WiFi.dnsIP().toString();
  MACAddressHW = WiFi.macAddress();
}
