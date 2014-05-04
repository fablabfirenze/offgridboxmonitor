#include "Adafruit_MAX31855.h"

//THERMOCOUPLE AMBIENT CONST
const int THERMO_ENV_DO = 22;//13
const int THERMO_ENV_CS = 24;//11
const int THERMO_ENV_CLK =26;//12

//THERMOCOUPLE PANEL CONST
const int THERMO_PANEL_DO = 23;//10
const int THERMO_PANEL_CS = 25;//8
const int THERMO_PANEL_CLK = 27;//9

//ADAFRUIT INTERFACE OBJECT DECLARATION 
Adafruit_MAX31855 thermocoupleEnvironment(THERMO_ENV_CLK, THERMO_ENV_CS, THERMO_ENV_DO);
Adafruit_MAX31855 thermocouplePanel(THERMO_PANEL_CLK, THERMO_PANEL_CS, THERMO_PANEL_DO);

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

//PUBLIC VARS
float panelTemp          = 0.0;
float ambientTemp        = 0.0;
float batteryVoltage     = 0.0;
int   batteryPercentage  = 0.0;
float waterLevel         = 0.0;
boolean isEnvironmentTempValid = false;  //true:indicate valid temp number; fales: temp read failed NAN 
boolean isPanelTempValid = false;  //true:indicate valid temp number; fales: temp read failed NAN
boolean debug = true;              //true:fro printing data in serial line

//MIX
boolean readSensorValue = true;
boolean sendValueToServer = true;

void setup() {
  if(debug == true){
    Serial.begin(9600); 
  }
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

  if(debug == true){
   Serial.print("Internal Panel Temp = ");
   Serial.println(thermocouplePanel.readInternal());
  }

   float c = (float)thermocouplePanel.readCelsius();
   
   if (isnan(c)) {
     isPanelTempValid = false;
     if(debug == true){
       Serial.println("Something wrong with Panel thermocouple!");
     }
   } else {
     isPanelTempValid = true;
     if(debug == true){
       Serial.print("PanelTemp = "); 
       Serial.println(c);
     }
   }
   if(debug == true){
     delay(1000);
   }
   return c;
}

//READ AMBIENT TEMPERATURE
//MICHELE - FRANCESCO
float getAmbientTemp(){

  if(debug == true){
   Serial.print("Internal Environment Temp = ");
   Serial.println(thermocoupleEnvironment.readInternal());
  }

   float c = (float)thermocoupleEnvironment.readCelsius();
   
   if (isnan(c)) {
     isEnvironmentTempValid = false;
     if(debug == true){
       Serial.println("Something wrong with Environment thermocouple!");
     }
   } else {
     isEnvironmentTempValid = true;
     if(debug == true){
       Serial.print("ambientTemp = "); 
       Serial.println(c);
     }
   }
   if(debug == true){
     delay(1000);
   }
   return c;
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
