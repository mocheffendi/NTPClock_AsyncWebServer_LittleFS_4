#include <FS.h>
#include <LittleFS.h>

// Initialize LittleFS
void initLittleFS() {
  if (!LittleFS.begin()) {
    //Serial.println("An error has occurred while mounting LittleFS");
  }
  //Serial.println("LittleFS mounted successfully");
}

// Read File from LittleFS
String readFile(fs::FS, const char * path){
  Serial.printf("[INFO] Reading file: %s\r\n", path);

  File file = LittleFS.open(path, "r");
  if (!file) {
    //Serial.println("Failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;

  file.close();
}

// Write file to LittleFS
void writeFile(fs::FS, const char * path, const char * message){
  Serial.printf("[INFO] Writing file: %s\r\n", path);

  File file = LittleFS.open(path, "w");
  if (!file) {
    //Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    //Serial.println("- file written");
  } else {
    //Serial.println("- frite failed");
  }
  delay(2000); // Make sure the CREATE and LASTWRITE times are different
  file.close();
}
