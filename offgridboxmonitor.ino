// Section for Temparature SENSOR - start
#include <Adafruit_MAX31855.h>
// #include "ogbQuantumWaterLevel.h"

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

int  LCD_CurrPage;              // Current page displayed for LCD_State = -1
unsigned long LCD_Page_Time = 15 * 1000;  // switch page Timeout
unsigned long LCD_CurrPageTime;          // Up Time of page

// Timeout for LCD off (millisecond)
unsigned long LCD_DIM  = 120000;
unsigned long LCD_TIME_ON;

unsigned long SAVE_TIMER = 0;
unsigned long SEND_TIMER = 0;

// SECTION FOR LCD DECLARATION - end

//SECTION FOR WATERLEVEL DECLARETION - start
const int WATER_LEVEL_SENSOR = A0;
//SECTION FOR WATERLEVEL DECLARETION - end

String logRow = "";

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


unsigned long *My_Timer[10];

void setup() {
  if(debug == true){
    Serial.begin(9600);
  }

  Serial.begin(9600);

  setup_battery();
  setup_counter();

  // to prevent millis reset, bind all variables to the array
  int idx0 = 0;
  My_Timer[idx0++] = &LCD_CurrPageTime;
  My_Timer[idx0++] = &LCD_TIME_ON;
  My_Timer[idx0++] = &SAVE_TIMER;
  My_Timer[idx0++] = &SEND_TIMER;
  My_Timer[idx0]   = 0x00;                // last entry MUST be null!!!


  setupRTC();
  setupSD();
  setupGSM();

  setupLCD();
}

void loop() {
  checkTimerOverflow();
  //READ SENSOR VALUES
  if(readSensorValue){
    panelTemp         = getPanelTemp();
    ambientTemp       = getAmbientTemp();
    batteryVoltage    = getBatteryVoltage();
    batteryPercentage = getBatteryPercentage();
    powerUsed         = getKWh();
    waterLevel        = getWaterLevel();

    // logToSd();
    // if (logToSd()) {
    //   Serial.println("Write finished.");
    // } else {
    //   Serial.println("Error writing.");
    // }
  }

  if(millis() > SAVE_TIMER){
    logToSd();
    SAVE_TIMER = millis()+5000;
  }

  if(millis() > SEND_TIMER){
    sendSms(logRow);
    SEND_TIMER = millis()+60000;
  }


  LCD_Refresh(Read_LCD_Button());


  delay(50);
}


unsigned long lastTime = 0;
void checkTimerOverflow(){
  unsigned long mil = millis();

  if(mil < lastTime){
    // Serial.println("\n\n\nRESET\n\n");
    // Serial.println(mil);

    for(int idx=0; My_Timer[idx]; idx++ ){
      *My_Timer[idx] -=  lastTime - mil;
    }

  }
  lastTime = mil;

}
