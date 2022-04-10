
#include <Sodaq_DS3231.h>

DateTime now2;

unsigned long epoch;

unsigned int localPort = 2390;      // local port to listen for UDP packets

//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
//const char* ntpServerName = "time.nist.gov";
char* ntpServerName = "pool.ntp.org";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

// SETUP RTC
char weekDay[][7] = {"AHAD",  "SENIN", "SELASA", "RABU",
                     "KAMIS", "JUMAT", "SABTU"
                    }; 
                    
char monthYear[][4] = {" ",   "JAN", "FEB", "MAR", "APR", "MEI", "JUN",
                       "JUL", "AGS", "SEP", "OKT", "NOV", "DES"
                      };
