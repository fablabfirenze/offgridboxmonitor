//
const int DISPLAY_SDA = 20;  
const int DISPLAY_SDL = 21;

float panelTemp      = 0.0;
float ambientTemp    = 0.0;
float batteryVoltage = 0.0;
float waterLevel     = 0.0;

boolean readSensorValue = true;
boolean sendValueToServer = true;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  //Timer lettura sensori
  if(readSensorValue){
    panelTemp      = getPanelTemp();
    ambientTemp    = getAmbientTemp();
    batteryVoltage = getBatteryVoltage();
    waterLevel     = getWaterLevel();
    updateDisplayValues();
  }
  
  if(sendValueToServer){
   //invio dati al server
  }
  
  delay(2000);
}

float getPanelTemp(){
  return 1; 
}

float getAmbientTemp(){
  return 1; 
}

float getBatteryVoltage(){
  return 1; 
}

float getWaterLevel(){
  return 1; 
}

void updateDisplayValues(){
  
}
