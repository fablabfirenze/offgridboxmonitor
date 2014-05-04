// Section for Temparature SENSOR - start
#include <Adafruit_MAX31855.h>

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

//SECTION FOR WATERLEVEL DECLARETION - start
const int WATER_LEVEL_SENSOR = A0;
//SECTION FOR WATERLEVEL DECLARETION - end

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
float powerProd          = 0.0;
float powerUsed          = 0.0;

//MIX
boolean readSensorValue = true;
boolean sendValueToServer = true;

void setup() {
  if(debug == true){
    Serial.begin(9600);
  }

  setupLCD();
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

  LCD_Refresh(Read_LCD_Button());

  delay(50);
}

//READ BATTERY TEMPERATURE (24 V BATTERY)
float getBatteryVoltage(){
  return batteryVoltage;
}
//READ BATTERY PERCENTAGE
int getBatteryPercentage(){
  return batteryPercentage;
}
