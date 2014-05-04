//READ WATER LEVEL (MAX TANK LEVEL 1500LT)
// FRANCESCA - TOMMASO
float getWaterLevel(){
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
}
