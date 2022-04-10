void textCenter1PKanan(int y, String Msg) {

  int center = ((Disp.width() - Disp.textWidth(Msg)) / 2) + (Disp.width() / 4);
  Disp.drawText(center, y, Msg);

}

void textCenter(int y, String Msg) {

  int center = int((Disp.width() - Disp.textWidth(Msg)) / 2);
  Disp.drawText(center, y, Msg);

}

void UpdateWaktu() {

  static long pM;
  static uint16_t d;


  if (millis() - pM > 1000) {
    d++;
    if (d < 2) {
      BacaRTC();
      //JadwalSholat();
      //TanggalHijriah();
    } else if (d < 60) { // Update setiap 60 detik
      rDet++;
      if (rDet > 59) {
        rMen++;
        rDet = 0;
        if (rMen > 59) {
          rJam++;
          rMen = 0;
        }
      }
    } else {
      d = 0;
    }
    pM = millis();
  }

}

void JamBesar1(uint16_t x) {

  //Serial.println("JamBesar1");
  char jam[3];
  char menit[3];

  sprintf(jam, "%02d", rJam);
  sprintf(menit, "%02d", rMen);

  static boolean huruf;

  static uint8_t y;
  static uint8_t d;
  static uint32_t pM;
  uint32_t cM = millis();

  static uint32_t pMPulse;
  static uint8_t pulse;

  if (cM - pMPulse >= 100) {

    pMPulse = cM;
    pulse++;

  }

  if (pulse > 8) {
    pulse = 0;
  }

  if (cM - pM > 35) {

    if (d == 0 and y < 20) {
      pM = cM;
      y++;
    }

    if (d  == 1 and y > 0) {
      pM = cM;
      y--;
    }

  }

  //if(cM - pM > 10000 and y == 20) {
  //d=1;
  //}

  if (y == 20) {
    Disp.drawRect(x + 14, 3 + pulse, x + 17, 11 - pulse, 0, 1);
  }

  if (y < 20) {
    Disp.drawRect(x + 14, 3, x + 18, 17, 0, 0);
  }

  //if(y == 0 and d == 1) {
  //d=0;
  //huruf = !huruf;
  //}

  //JAM
  //if (huruf) {
  Disp.setFont(ElektronMart6x16);
  //} else {
  //Disp.setFont(ElektronMartArabic6x16);
  //}
  Disp.drawText(x + 1, y - 20, jam);


  //MENIT
  //if (huruf) {
  Disp.setFont(ElektronMart6x16);
  //} else {
  //Disp.setFont(ElektronMartArabic6x16);
  //}
  Disp.drawText(x + 18, y - 20, menit);
}

void JamBesar2(uint16_t x) {

  //Serial.println("JamBesar2");
  char jam[3];
  char menit[3];
  char detik[3];

  sprintf(jam, "%02d", rJam);
  sprintf(menit, "%02d", rMen);
  sprintf(detik, "%02d", rDet);

  static uint8_t y;
  static uint8_t d;
  static uint32_t pM;
  uint32_t cM = millis();

  static uint32_t pMPulse;
  static uint8_t pulse;

  if (cM - pMPulse >= 100) {
    pMPulse = cM;
    pulse++;
  }

  if (pulse > 8) {
    pulse = 0;
  }

  if (cM - pM > 35) {
    if (d == 0 and y < 20) {
      pM = cM;
      y++;
    }
    if (d  == 1 and y > 0) {
      pM = cM;
      y--;
    }
  }

  if (cM - pM > 10000 and y == 20) {
    d = 1;
  }

  if (y == 20) {
    Disp.drawRect(x + 15, 3 + pulse, x + 18, 11 - pulse, 0, 1);
  }

  if (y < 20) {
    Disp.drawRect(x + 15, 3, x + 18, 11, 0, 0);
  }

  if (y == 0 and d == 1) {
    d = 0;
    huruf = !huruf;
  }

  //JAM
  if (huruf) {
    Disp.setFont(ElektronMart6x16);
  } else {
    Disp.setFont(ElektronMartArabic6x16);
  }
  Disp.drawText(x + 1, y - 20, jam);

  //MENIT
  if (huruf) {
    Disp.setFont(ElektronMart5x6);
  } else {
    Disp.setFont(ElektronMartArabic5x6);
  }
  Disp.drawText(x + 20, y - 20, menit);

  //DETIK
  if (huruf) {
    Disp.setFont(ElektronMart5x6);
  } else {
    Disp.setFont(ElektronMartArabic5x6);
  }
  Disp.drawText(x + 20, y - 20 + 8, detik);

  //Serial.println(String(jam) + ":" + String(menit) + ":" + String(detik));
}

void JamBesar3(uint16_t x) {

  //Serial.println("JamBesar3");
  char jam[3];
  char menit[3];

  sprintf(jam, "%02d", rJam);
  sprintf(menit, "%02d", rMen);

  static boolean huruf;

  static uint8_t y;
  static uint8_t d;
  static uint32_t pM;
  uint32_t cM = millis();

  static uint32_t pMPulse;
  static uint8_t pulse;

  if (cM - pMPulse >= 100) {

    pMPulse = cM;
    pulse++;

  }

  if (pulse > 8) {
    pulse = 0;
  }

  if (cM - pM > 35) {

    if (d == 0 and y < 20) {
      pM = cM;
      y++;
    }

    if (d  == 1 and y > 0) {
      pM = cM;
      y--;
    }

  }

  if (cM - pM > 10000 and y == 20) {
    d = 1;
  }

  if (y == 20) {
    Disp.drawRect(x + 14, 3 + pulse, x + 17, 11 - pulse, 0, 1);
  }

  if (y < 20) {
    Disp.drawRect(x + 14, 3, x + 18, 17, 0, 0);
  }

  if (y == 0 and d == 1) {
    d = 0;
    huruf = !huruf;
  }

  //JAM
  if (huruf) {
    Disp.setFont(ElektronMart6x16);
  } else {
    Disp.setFont(ElektronMartArabic6x16);
  }
  Disp.drawText(x + 1, y - 20, jam);


  //MENIT
  if (huruf) {
    Disp.setFont(ElektronMart6x16);
  } else {
    Disp.setFont(ElektronMartArabic6x16);
  }
  Disp.drawText(x + 18, y - 20, menit);
}

void TampilIP() {

  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 50;
  static uint32_t x;

  int width = Disp.width();
  int fullScroll = Disp.textWidth(LocalIPStr) + width;

  Disp.setFont(ElektronMart6x8);
  textCenter(0, "IP :");
  //Disp.drawRect(0,6,Disp.width(),6,1,1);

  if (cM - pM > Kecepatan) {
    pM = cM;
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      tampil = 2;
    }
    Disp.drawText(width - x, 8, LocalIPStr);
  }
}

void TampilInfo() {

  static uint32_t pM;
  uint32_t cM = millis();

  static uint8_t flag;

  if (cM - pM > 5000) {

    pM = cM;
    flag++;

    if ((!huruf) && (flag >= 5)) {
      flag = 0;
      //Disp.drawRect(32,0,64,15,0,0);
      Disp.clear();
      tampil = 3;
    }
  }
}

void TampilTanggal() {

  char hari[8];
  char tanggal[7]; // 21 SEP

  static uint32_t pM;
  uint32_t cM = millis();

  static uint8_t flag;

  if (cM - pM > 3000) {

    pM = cM;
    flag++;

    sprintf(hari, "%s", namaHari[rHar]);
    sprintf(tanggal, "%02d %s", rTgl, namaBulan[rBul]);

    Disp.setFont(ElektronMart5x6);
    textCenter(0, hari);
    textCenter(8, tanggal);

    if (flag >= 2) {
      flag = 0;
      //Disp.drawRect(32, 0, 64, 15, 0, 0);
      //tmpinfo = 1;
      Disp.clear();
      tampil = 4;
    }
  }
}

void TampilSuhu() {

  char Temp[3];
  //tampilsuhu = true;
  static uint32_t pM;
  uint32_t cM = millis();

  static uint8_t flag;

  if (cM - pM > 3000) {

    pM = cM;
    flag++;

    //Serial.println(TempStr);
    TempStr.toCharArray(Temp, 3);
    //sprintf(Humi, "%d", HumiStr);
    //TempStr = String(Temp) + " *C";
    //Serial.println(TempStr);
    Disp.setFont(ElektronMart5x6);
    //Disp.drawText(2, 0, "Temp");
    textCenter(0, "Temp :");
    Disp.drawText(6, 8, Temp);
    Disp.drawText(20, 8, "*C");
    //textCenter(8, Temp);


    if (flag >= 2) {
      flag = 0;
      //Disp.drawRect(32, 0, 64, 15, 0, 0);
      Disp.clear();
      tampil = 5;
    }
  }
}

void TampilKelembaban() {

  char Humi[3];
  //tampilsuhu = true;
  static uint32_t pM;
  uint32_t cM = millis();

  static uint8_t flag;

  if (cM - pM > 3000) {

    pM = cM;
    flag++;
    //Serial.println(HumiStr);
    HumiStr.toCharArray(Humi, 3);
    //sprintf(Humi, "%d", HumiStr);
    //HumiStr = String(Humi) + " %";

    Disp.setFont(ElektronMart5x6);
    Disp.drawText(1, 0, "Humidity:");
    Disp.drawText(7, 8, Humi);
    Disp.drawText(21, 8, "%");
    //textCenter(8, Humi);

    if (flag >= 2) {

      flag = 0;

      //Disp.drawRect(32, 0, 64, 15, 0, 0);
      Disp.clear();
      tampil = 2;
    }
  }
}



//--------------------------
// TAMPILKAN SCROLLING TEKS

void TampilRunningText() {

  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 50;
  static uint32_t x;

  int width = Disp.width();
  int fullScroll = Disp.textWidth(runningtext) + width;

  Disp.setFont(ElektronMart6x8);
  textCenter(0, "Note:");
  //Disp.drawRect(0,6,Disp.width(),6,1,1);

  if (cM - pM > Kecepatan) {
    pM = cM;
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      tampil = 2;
    }
    Disp.drawText(width - x, 8, runningtext);
  }
}
