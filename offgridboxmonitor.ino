
//DISPLAY CONST
const int LCD_SDA = 20;
const int LCD_SDL = 21;

// Button Pin
const int  LCD_Button = 4;

//WATER CONST
const int WATER_LEVEL_PIN = A0;

//GSM MODULE CONST
const int GSM_RX = 2;
const int GSM_TX = 3;
const int GSM_RESET = 7;

//SD CONST
const int SD_SPI_1 = 2;
const int SD_SPI_2 = 3;
const int SD_SPI_3 = 3;

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

  LCD(digitalRead(LCD_BUTTON));

  //delay(2000);
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

//READ WATER LEVEL (MAX TANK LEVEL 1500LT)
float getWaterLevel(){

  float hmax = 95; // [cm] ch 1500 specification  (max value using formula)
  float Vempty = 1.30; //[V] @h = 0 
  float Vfull = 2.33; //[V] @h = hmax
  float Delta = (Vfull-Vempty)/hmax; // [V]/[cm]
  float L = 163; //tank length CH 1500 [cm]
  float R = 57.75; //radius tank CH 1500 [cm]
 
  int sensorValue = analogRead(A0);
  float Vactual = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
 
  //float V = Vempty+Delta*h;
  float h = (Vactual-Vempty)/Delta; //normalized height
  
  float liters = L*(pow(R,2)*acos((R-h)/R)+ (h-R)*sqrt( 2*h*R - pow(h,2)))/1000; //volume = area under the arc * length --> 1dm^3 = 1000cm^3 

  if(h > 95){ //check max liters = 1500 @95cm as in the formula
    liters = 1500; 
  }
  
  if (h < 2.82) { //chack min liters @h=2.82cm
     h = 0;
     liters = 0;     
  }
  
  return liters;
}

//UPDATE DISPLAY VALUES
void updateDisplayValues(){

}
