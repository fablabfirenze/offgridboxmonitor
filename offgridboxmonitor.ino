<<<<<<< HEAD
=======
// Section for Temparature SENSOR - start
>>>>>>> Temp Sensor added + LCD rev2
#include "Adafruit_MAX31855.h"

//THERMOCOUPLE AMBIENT CONST
const int THERMO_ENV_DO = 22;//13
const int THERMO_ENV_CS = 24;//11
const int THERMO_ENV_CLK =26;//12

//THERMOCOUPLE PANEL CONST
const int THERMO_PANEL_DO = 23;//10
const int THERMO_PANEL_CS = 25;//8
const int THERMO_PANEL_CLK = 27;//9

<<<<<<< HEAD

//WATERLEVEL  CONST
const int WATER_LEVEL_SENSOR = A0;
=======
//ADAFRUIT INTERFACE OBJECT DECLARATION 
Adafruit_MAX31855 thermocoupleEnvironment(THERMO_ENV_CLK, THERMO_ENV_CS, THERMO_ENV_DO);
Adafruit_MAX31855 thermocouplePanel(THERMO_PANEL_CLK, THERMO_PANEL_CS, THERMO_PANEL_DO);

boolean isEnvironmentTempValid = false;  //true:indicate valid temp number; fales: temp read failed NAN 
boolean isPanelTempValid = false;  //true:indicate valid temp number; fales: temp read failed NAN
boolean debug = false;              //true:fro printing data in serial line
// Section for Temparature SENSOR - end

// SECTION FOR LCD DECLARATION - start
// LCD DISPLAY CONST
const int LCD_SDA  = 20;
const int LCD_SDL  = 21;
const int LCD_ADDR = 0x3F;
const int LCD_NCAR = 20;
const int LCD_NROW = 4;
// LCD Button Pin
const int LCD_Button = 4;
// SECTION FOR LCD DECLARATION - end
>>>>>>> Temp Sensor added + LCD rev2


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
// All variables must be float!!!
float panelTemp          = 0.0;
float ambientTemp        = 0.0;
float batteryVoltage     = 0.0;
float batteryPercentage  = 0.0;
float waterLevel         = 0.0;
<<<<<<< HEAD
boolean isEnvironmentTempValid = false;  //true:indicate valid temp number; fales: temp read failed NAN 
boolean isPanelTempValid = false;  //true:indicate valid temp number; fales: temp read failed NAN
boolean debug = true;              //true:fro printing data in serial line
=======
float powerProd          = 0.0;
float powerUsed          = 0.0;
>>>>>>> Temp Sensor added + LCD rev2

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
  }
  
  if(sendValueToServer){
   //SEND DATA TO THE SERVER
  }
<<<<<<< HEAD
  
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
=======

  LCD_Refresh(Read_LCD_Button());

  delay(50);
>>>>>>> Temp Sensor added + LCD rev2
}



//READ BATTERY TEMPERATURE (24 V BATTERY)
float getBatteryVoltage(){
<<<<<<< HEAD
  return 1; 
=======
  return batteryVoltage;
>>>>>>> Temp Sensor added + LCD rev2
}
//READ BATTERY PERCENTAGE
int getBatteryPercentage(){
  return batteryPercentage; 
}

//READ WATER LEVEL (MAX TANK LEVEL 1500LT)
// FRANCESCA - TOMMASO
float getWaterLevel(){
<<<<<<< HEAD
  
  float tankHeight = 123; // [cm] total height excursion
 
  float Vempty = 1.30; //[V] @h = 0
  float Vfull = 2.61; //[V] @h = tankHeight
  float Delta = (Vfull-Vempty)/tankHeight; // [V]/[cm]
  
  int sensorValue = analogRead(WATER_LEVEL_SENSOR);
  float Vactual = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
 
  float h = (Vactual-Vempty)/Delta; //normalized height
  

  // VOLUME COMPUTATION
  float hmax = 95; // [cm] CH 1500 TANK specification  (height at which TANK volume is 1500 liters - max value using formula for liters)
  float L = 163; //tank length CH 1500 [cm]
  float R = 57.75; //radius tank CH 1500 [cm]
  float liters = L*(pow(R,2)*acos((R-h)/R)+ (h-R)*sqrt( 2*h*R - pow(h,2)))/1000; //volume = area under the arc * length --> 1dm^3 = 1000cm^3 

  if(h<=0){
    liters = 0; 
  }

  if(h>=2*R){ //check max liters = 1500 @2*R as in the formula
    liters = 1500; 
  } 
  return liters;
=======
  return waterLevel;
>>>>>>> Temp Sensor added + LCD rev2
}

//UPDATE DISPLAY VALUES
void updateDisplayValues(){
<<<<<<< HEAD
  
}
=======

}
>>>>>>> Temp Sensor added + LCD rev2
