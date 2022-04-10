//char weatherHostName [80] = "https://alhikmah.sekolahku.id/getCurrentWeather/1351/asiqownolqwiqoglk/1";
//const uint8_t fingerprint[20] = {0x2a, 0x06, 0xc5, 0x3f, 0x7f, 0xf5, 0x33, 0x0e, 0x75, 0xa0, 0x92, 0x8b, 0x02, 0xe0, 0xe4, 0x8d, 0xc7, 0x5b, 0xb8, 0xaf};

//http://api.openweathermap.org/data/2.5/weather?q=Surabaya,ID&APPID=377940e26eb038f489fbd04274a79204

String httpsGETRequest(const char* serverName) {

  WiFiClientSecure httpsClient;
  HTTPClient http;
  httpsClient.setInsecure();
  //httpsClient.setTimeout(10000);
  //newDelay(100);

  httpsClient.connect(serverName, 443);

  // Your IP address with path or Domain name with URL path
  http.begin(httpsClient, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("[HTTP] HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("[HTTP] Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  server.begin();
  return payload;
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

bool GETOnlineWeatherData()
{
  // Load values saved in LittleFS
  weatherhostname = readFile(LittleFS, weatherhostnamePath);

  jsonBuffer = httpsGETRequest(weatherhostname.c_str());
  Serial.println(jsonBuffer);

  myObject = JSON.parse(jsonBuffer);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined")
  {
    //Serial.println("Parsing input failed!");
    temp = 0;
    temperature = 0;
    humidity = 0;
    humidityD = 0;
    return false;
  }

  //    Serial.print("JSON object = ");
  //    Serial.println(myObject);

  // myObject.keys() can be used to get an array of all the keys in the object
  JSONVar keys = myObject.keys();

  for (int i = 0; i < keys.length(); i++)
  {
    JSONVar value = myObject[keys[i]];
    String valueStr = JSONVar::stringify(value);
    if (valueStr[0] == '"')
    {
      valueStr = valueStr.substring(1, (valueStr.length() - 1));
    }
    //      Serial.println("valueStr : " + valueStr);
    if (strcasecmp(keys[i], "epoch_timestamp") == 0)
    {
      epochstr = valueStr;
      //temperature = (int) round(temp);
      Serial.println("\t[EPOCH] now : " + (epochstr));
      //TempStr = String(temp);
      
      //long epochlong = epochstr.toInt()+2500;
      //Serial.print("[INFO] Set Epoch to RTC 3231 :");
      //Serial.println(epochlong);
      //rtc.setEpoch(epochlong);

    }

    if (strcasecmp(keys[i], "temp") == 0)
    {
      temp = valueStr.toDouble();
      temperature = (int) round(temp);
      Serial.println("\t[WEATHER] Temperature : " + String(temp));
      TempStr = String(temp);

    }

    if (strcasecmp(keys[i], "humidity") == 0)
    {
      humidityD = valueStr.toDouble();
      humidity = (int) round(humidityD);
      Serial.println("\t[WEATHER] Humidity : " + String(humidityD));
      HumiStr = String(humidityD);
    }
  }
  return true;
}

void ambildataWeather() {
  bool onlineWeatherGetResult = GETOnlineWeatherData();
  Serial.printf("[INFO] GETOnlineWeatherData result:%d temp:%f hum:%f\n", onlineWeatherGetResult, temp, humidityD);
}



/*
void WeatherUpdate() {
  if (WiFi.status() == WL_CONNECTED) {

    timer.disable(TimerJam);
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + String(ClockVar.City) + "," + countryCode + "&APPID=" + String(ClockVar.openWeatherMapApiKey) + "&units=metric";

    jsonBuffer = httpGETRequest(serverPath.c_str());
    Serial.println(jsonBuffer);
    JSONVar myObject = JSON.parse(jsonBuffer);

    // JSON.typeof(jsonVar) can be used to get the type of the var
    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing input failed!");
      return;
    }

    Serial.print("JSON object = ");
    Serial.println(myObject);
    Serial.print("Temperature: ");
    Serial.println(myObject["main"]["temp"]);
    String jsonString =  JSON.stringify(myObject["main"]["temp"]);

    //ClockVar.temperature = jsonString.toFloat();
    strcpy(ClockVar.temperature, myObject["main"]["temp"]);
    Serial.println(ClockVar.temperature);
    /*
      dmd.selectFont(Droid_Sans_16);
      dmd.begin();
      dmd.clearScreen();
      String(temperature).toCharArray(Suhu, 3);
      String SuhuStr = "Temperature : " + Suhu;
      char *next = SuhuStr;
      while (*next) {
      Serial.print(*next);
      box.print(*next);
      newDelay(300);
      next++;
      }
    */
    /*
    dmd.clearScreen();
    String suhu = Konversi(String(ClockVar.temperature).toFloat());
    dmd.selectFont(Arial14);
    if (String(ClockVar.temperature).toFloat() > 0)
    {
      dmd.drawString(1, 1, suhu);
      dmd.drawString(22, 1, "C");

      //Gambar simbol degree..
      dmd.drawFilledBox(19, 1, 20, 4);
      dmd.drawFilledBox(18, 1, 18, 2);
      dmd.drawFilledBox(19, 5, 19, 5);
    }
    else
    {
      //    dmd.drawString(1, 1, "--");
      TampilTanggal();
    }
    newDelay(3000);

    Serial.print("Pressure: ");
    Serial.println(myObject["main"]["pressure"]);
    Serial.print("Humidity: ");
    Serial.println(myObject["main"]["humidity"]);
    //ClockVar.humidity = int(myObject["main"]["humidity"]);
    strcpy(ClockVar.humidity, myObject["main"]["humidity"]);
    dmd.clearScreen();
    String humi = Konversi(String(ClockVar.humidity).toInt());
    dmd.selectFont(Arial14);
    if (ClockVar.humidity > 0)
    {
      dmd.drawString(1, 1, humi);
      dmd.drawString(19, 1, "%");

      //Gambar simbol degree..

    }
    else
    {
      //    dmd.drawString(1, 1, "--");
      TampilTanggal();
    }
    newDelay(3000);
    Serial.print("Wind Speed: ");
    Serial.println(myObject["wind"]["speed"]);

    timer.enable(TimerJam);
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}
*/
