//DISPLAY CONST
const int DISPLAY_SDA = 20;  
const int DISPLAY_SDL = 21;

//GSM MODULE CONST
const int GSM_RX = 2;
const int GSM_TX = 3;
const int GSM_RESET = 7;

//SD CONST
const int SD_SPI_1 = 2;  
const int SD_SPI_2 = 3;
const int SD_SPI_2 = 3;

//PUBLIC VARS
float panelTemp          = 0.0;
float ambientTemp        = 0.0;
float batteryVoltage     = 0.0;
int   batteryPercentage  = 0.0;
float waterLevel         = 0.0;

//MIX
boolean readSensorValue = true;
boolean sendValueToServer = true;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  //READ SENSOR VALUES
  if(readSensorValue){
    panelTemp         = getPanelTemp();
    ambientTemp       = getAmbientTemp();
    batteryVoltage    = getBatteryVoltage();
    batteryPercentage = getBatteryPercentage();
    waterLevel        = getWaterLevel();
    updateDisplayValues();
  }
  
  if(sendValueToServer){
   //SEND DATA TO THE SERVER
  }
  
  delay(2000);
}

//READ PANEL TEMPERATURE
//MICHELE - FRANCESCO
float getPanelTemp(){
  return 1; 
}

//READ AMBIENT TEMPERATURE
//MICHELE - FRANCESCO
float getAmbientTemp(){
  return 1; 
}

//READ BATTERY TEMPERATURE (24 V BATTERY)
float getBatteryVoltage(){
  return 1; 
}
//READ BATTERY PERCENTAGE
int getBatteryPercentage(){
  return 1; 
}

//READ WATER LEVEL (MAX TANK LEVEL 1200LT)
float getWaterLevel(){
  return 1; 
}

//UPDATE DISPLAY VALUES
void updateDisplayValues(){
  
}
