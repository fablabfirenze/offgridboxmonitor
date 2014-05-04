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


