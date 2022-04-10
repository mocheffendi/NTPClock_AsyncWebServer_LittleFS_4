// ------------------------
// SETUP RTC

RtcDateTime now;
char namaHari[][7] = {"AHAD", "SENIN", "SELASA", "RABU", "KAMIS", "JUM'AT", "SABTU", "AHAD"}; // array hari, dihitung mulai dari senin, hari senin angka nya =0,
char namaBulan[][4] = { "DES", "JAN", "FEB", "MAR", "APR", "MEI", "JUN", "JUL", "AGU", "SEP", "OKT", "NOV", "DES" };
char hariHijriah[][8] = {"AHAD", "ISNAIN", "SULASA", "ARBI'A", "KHAMIS", "JUMU'AH", "SABT", "AHAD"};
char bulanHijriah[][4] = { "ZLH", "MUH", "SAF", "RAW", "RAK", "JUW", "JUK", "RAJ", "SYB", "RAM", "SYW", "ZLK", "ZLH" };


uint8_t rJam;
uint8_t rMen;
uint8_t rDet;
uint8_t rTgl;
uint8_t rHar;
uint8_t rBul;
uint16_t rTah;
int celsius;


// PrayerTimes
//double times[sizeof(TimeName)/sizeof(char*)];


//----------------------------------------------------------------------
// I2C_ClearBus menghindari gagal baca RTC (nilai 00 atau 165)

int I2C_ClearBus() {
  
  #if defined(TWCR) && defined(TWEN)
    TWCR &= ~(_BV(TWEN)); //Disable the Atmel 2-Wire interface so we can control the SDA and SCL pins directly
  #endif

  pinMode(SDA, INPUT_PULLUP); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
  pinMode(SCL, INPUT_PULLUP);

  delay(2500);  // Wait 2.5 secs. This is strictly only necessary on the first power
  // up of the DS3231 module to allow it to initialize properly,
  // but is also assists in reliable programming of FioV3 boards as it gives the
  // IDE a chance to start uploaded the program
  // before existing sketch confuses the IDE by sending Serial data.

  boolean SCL_LOW = (digitalRead(SCL) == LOW); // Check is SCL is Low.
  if (SCL_LOW) { //If it is held low Arduno cannot become the I2C master. 
    return 1; //I2C bus error. Could not clear SCL clock line held low
  }

  boolean SDA_LOW = (digitalRead(SDA) == LOW);  // vi. Check SDA input.
  int clockCount = 20; // > 2x9 clock

  while (SDA_LOW && (clockCount > 0)) { //  vii. If SDA is Low,
    clockCount--;
  // Note: I2C bus is open collector so do NOT drive SCL or SDA high.
    pinMode(SCL, INPUT); // release SCL pullup so that when made output it will be LOW
    pinMode(SCL, OUTPUT); // then clock SCL Low
    delayMicroseconds(10); //  for >5uS
    pinMode(SCL, INPUT); // release SCL LOW
    pinMode(SCL, INPUT_PULLUP); // turn on pullup resistors again
    // do not force high as slave may be holding it low for clock stretching.
    delayMicroseconds(10); //  for >5uS
    // The >5uS is so that even the slowest I2C devices are handled.
    SCL_LOW = (digitalRead(SCL) == LOW); // Check if SCL is Low.
    int counter = 20;
    while (SCL_LOW && (counter > 0)) {  //  loop waiting for SCL to become High only wait 2sec.
      counter--;
      delay(100);
      SCL_LOW = (digitalRead(SCL) == LOW);
    }
    if (SCL_LOW) { // still low after 2 sec error
      return 2; // I2C bus error. Could not clear. SCL clock line held low by slave clock stretch for >2sec
    }
    SDA_LOW = (digitalRead(SDA) == LOW); //   and check SDA input again and loop
  }
  if (SDA_LOW) { // still low
    return 3; // I2C bus error. Could not clear. SDA data line held low
  }

  // else pull SDA line low for Start or Repeated Start
  pinMode(SDA, INPUT); // remove pullup.
  pinMode(SDA, OUTPUT);  // and then make it LOW i.e. send an I2C Start or Repeated start control.
  // When there is only one I2C master a Start or Repeat Start has the same function as a Stop and clears the bus.
  /// A Repeat Start is a Start occurring after a Start with no intervening Stop.
  delayMicroseconds(10); // wait >5uS
  pinMode(SDA, INPUT); // remove output low
  pinMode(SDA, INPUT_PULLUP); // and make SDA high i.e. send I2C STOP control.
  delayMicroseconds(10); // x. wait >5uS
  pinMode(SDA, INPUT); // and reset pins as tri-state inputs which is the default state on reset
  pinMode(SCL, INPUT);
  return 0; // all ok
  
}



// MULAI RTC DS3231

void mulaiRTC() {

  int rtn = I2C_ClearBus(); // clear the I2C bus first before calling Wire.begin()
  if (rtn != 0) {
    //Serial.println(F("I2C bus error. Could not clear"));
    if (rtn == 1) {
      //Serial.println(F("SCL clock line held low"));
    } else if (rtn == 2) {
      //Serial.println(F("SCL clock line held low by slave clock stretch"));
    } else if (rtn == 3) {
      //Serial.println(F("SDA data line held low"));
    }
  } else { // bus clear, re-enable Wire, now can start Wire Arduino master
    Wire.begin();
  }
  
  Rtc.Begin();

  if (!Rtc.GetIsRunning()) {
    
    Rtc.SetIsRunning(true);
    
  }
  
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  
  //Serial.println("Setup RTC selesai");
  
}


//----------------------------------------------------------------------
// UPDATE WAKTU

void BacaRTC() {
  RtcDateTime now = Rtc.GetDateTime();
  RtcTemperature temp = Rtc.GetTemperature();
  celsius = temp.AsFloatDegC();
  rJam = now.Hour();
  rMen = now.Minute();
  rDet = now.Second();
  rTgl = now.Day();
  rHar = now.DayOfWeek();
  rBul = now.Month();
  rTah = now.Year();
  Serial.println(String(rJam)+":"+String(rMen)+":"+String(rDet));
}
