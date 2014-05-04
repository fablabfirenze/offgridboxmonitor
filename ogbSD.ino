#include <SD.h>

const int chipSelect = 53;

/*
 * SD Card init
 */
void setupSD()
{
  
  Serial.print("Initializing SD card...");
  pinMode(53, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  
  Serial.println("SD initialized.");

}

boolean logToSd() {
  
  DateTime now = rtc.now();
  String dataString = "";
  String separator = ",";
  String clientId = "12345";
  String timestamp = String(now.unixtime(), DEC);
  boolean isLogged = false;
  String today = String(now.year(), DEC) + String(now.month(), DEC) + String(now.day(), DEC) ;
  today.concat(".txt");
  char buffer[6];

  dataString = clientId + separator + timestamp + separator + dtostrf(panelTemp, 3, 2, buffer) + separator + dtostrf(ambientTemp, 3, 2, buffer) + separator + dtostrf(batteryVoltage, 3, 2, buffer) + separator + dtostrf(batteryPercentage, 3, 2, buffer) + separator + dtostrf(waterLevel, 3, 2, buffer);
  
  char fileName[today.length()+1];
  today.toCharArray(fileName, sizeof(fileName));
  
  File dataFile = SD.open(fileName, FILE_WRITE);
  
  // if the file is available, write to it:
  if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
      isLogged = true;
      sendSms(dataString);
  } else {
      Serial.println("Error opening log file");
  }
  
  return isLogged;
}

