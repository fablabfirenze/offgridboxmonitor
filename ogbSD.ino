#include <SD.h>

const int chipSelect = 53;


/*
 * SD Card init
 */
void setupSD()
{

  // Serial.print("Initializing SD card...");
  pinMode(53, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    // Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }

  // Serial.println("SD initialized.");

}

boolean logToSd() {

  DateTime now = rtc.now();

  logRow = "";
  String dataString = "";
  String separator = "\n";
  String clientId = "12345";
  String timestamp = String(now.unixtime(), DEC);
  boolean isLogged = false;
  String today = String(now.year(), DEC) + String(now.month(), DEC) + String(now.day(), DEC) ;
  today.concat(".txt");
  char buffer[8];
  char fileName[today.length()+1];
  today.toCharArray(fileName, sizeof(fileName));

  logRow += clientId;
  logRow += separator;
  logRow += timestamp;
  logRow += separator;
  String panelTempStr = dtostrf(panelTemp, 3, 2, buffer);
  logRow += panelTempStr;
  logRow += separator;
  String ambientTempStr = dtostrf(ambientTemp, 3, 2, buffer);
  logRow += ambientTempStr;
  logRow += separator;
  String batteryVoltageStr = dtostrf(batteryVoltage, 3, 2, buffer);
  logRow += batteryVoltageStr;
  logRow += separator;
  String batteryPercentageStr = dtostrf(batteryPercentage, 3, 2, buffer);
  logRow += batteryPercentageStr;
  logRow += separator;
  String waterLevelStr = dtostrf(waterLevel, 5, 2, buffer);
  logRow += waterLevelStr;


  File dataFile = SD.open(fileName, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {

      dataFile.print(clientId);
      dataFile.print(separator);
      dataFile.print(timestamp);
      dataFile.print(separator);
      dataFile.print(panelTempStr);
      dataFile.print(separator);
      dataFile.print(ambientTempStr);
      dataFile.print(separator);
      dataFile.print(batteryVoltageStr);
      dataFile.print(separator);
      dataFile.print(batteryPercentageStr);
      dataFile.print(separator);
      dataFile.print(waterLevelStr);
      dataFile.println("");

      dataFile.close();
      // print to the serial port too:
      // Serial.println(dataString);
      isLogged = true;
      // sendSms(dataString);
  } else {
      // Serial.println("Error opening log file");
  }

  return isLogged;
}

