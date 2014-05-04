#define DEBUG
#define BATTERY_PIN A2
#define COUNTER_PIN 5 //This rappresents the PIN 18 on the Arduino Mega interpretate as an interrupt

//----------------------------------ALL THIS PARAMETER HAVE TO BE CHANGED BY THE VALUES REPORTED ON THE DATA-SHEET OF THE BATTERIES--------------------------------
#define BATTERY_FULLY_CHARGED 27.0f                                   //The value of the series of batteries after complete chargin, THIS CONSTANT HAVE TO BE RE-MEASURED WHEN THE BATTERIES ARE FULLY CHARGED
#define BATTERY_FULLY_CHARGED_PROP 3.5978f                           //The value of the battery seen by the voltage divider, THIS CONSTANT HAVE TO BE RE-MEASURED WHEN THE BATTERIES ARE FULLY CHARGED
#define BATTERY_CONST BATTERY_FULLY_CHARGED/BATTERY_FULLY_CHARGED_PROP
#define VCC 5.01f

#define NUM_OF_STEP 15 //It must be the number of the element in both the below arrays
const float voltage[] = {26.40,26.26,26.16,26.04,25.92,25.80,25.72,25.64,25.56,25.48,25.40,25.24,25.08,24.96,24.88}; //THIS VALUE HAVE TO BE CHANGED WITH THE CORRECT VALUES FROM THE BATTERY'S DATASHEET
const int perc_step[] = {100,95,90,85,80,75,70,65,60,55,50,40,30,20,10};                                             //THIS VALUE HAVE TO BE CHANGED WITH THE CORRECT VALUES FROM THE BATTERY'S DATASHEET
//-------------------------------------------------------------------------------END-----------------------------------------------------------------------------

unsigned int counter_variable = 0;

void setup_battery()
{
  pinMode(BATTERY_PIN,INPUT);
}

void setup_counter()
{
  pinMode(COUNTER_PIN,INPUT);
}

//READ BATTERY TEMPERATURE (24 V BATTERY)
float getBatteryVoltage(){
  float value = analogRead(BATTERY_PIN);
  float vout = ((value * VCC) / 1023.0f);

  float second_vout;

  #ifdef DEBUG
    Serial.print("ADC read: ");
    Serial.println(value);
    Serial.print(vout);
    Serial.println("V");
  #endif


  //Now we have the voltage between 0-3.5
  //We must convert it to the range 0-24 and return it

  second_vout = (vout * BATTERY_CONST);
  #ifdef DEBUG
    Serial.print(second_vout);
    Serial.print("V");
    Serial.print("\n");
  #endif

  return vout;
}
//READ BATTERY PERCENTAGE
float getBatteryPercentage()
{
  float value = analogRead(BATTERY_PIN);
  float vout = ((value * VCC) / 1023.0f);
  float val;
  float second_vout;

  //Now we have the voltage between 0-3.5
  //We must convert it to the range 0-24 and return it

  second_vout = (vout * BATTERY_CONST);
  val = 0;
  for(int i=0;i<NUM_OF_STEP;i++)
  {
    if(second_vout > voltage[i])
    {
      //We can add here the map function to approximate a percentage value
     val = map(second_vout, voltage[i], voltage[i-1], perc_step[i], perc_step[i-1]);
     #ifdef DEBUG
       Serial.print(val);
       Serial.println("%");
     #endif

      break;
    }
  }

  return val;
}

float getKWh()
{
   #ifndef DEBUG
     Serial.print("KWh:");
     Serial.println(counter_variable/1000);
   #endif
}

void counter()
{
  counter_variable++;
}
