#ifndef LCD_OffGridBox
#define LCD_OffGridBox

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3F,20,4);

/*
 *
 * Pin Configuration
 *
 * 4 = Push button to change value on display
 * 20,21 LCD Display
 *
 */

//PUBLIC VARS
// float panelTemp      = 123.0;
// float ambientTemp    = 12.0;
// float waterLevel     = 1200.0;
// float batteryVoltage = 24.0;

int   time_HH = 24;                           // hour of last refresh
int   time_mm = 59;                           // min  of last refresh

/*
 * Variable definition for display values
 *
 */

/*
 * Displayed value
 * 0 Setup
 * 1 PanelTemp
 * 2 AmbientTemp
 * 3 WaterLevel
 * 4 batteryVoltage
 * 5 All Values
 */
int LCD_State        = 1;
/*
 * Display Mode
 *
 * 1 = Show All Values
 * 2 = Show Single Value
 */
int LCD_Mode   = 2;
/*
 * Panel Temperature
 */
const char   PanelTempStr[] = "Panel Temp.";
const char   PanelTempUM[]  = "\"C";
const float  PanelTempMin   = 0.0;
const float  PanelTempMax   = 130.0;
/*
 * Ambient Temperature
 */
const char   AmbientTempStr[] = "Ambient Temp.";
const char   AmbientTempUM[]  = "\"C";
const float  AmbientTempMin   = 0.0;
const float  AmbientTempMax   = 70.0;
/*
 * Water Level
 */
const char   WaterLevelStr[] = "Water Level";
const char   WaterLevelUM[]  = "L";
const float  WaterLevelMin   = 0.0;
const float  WaterLevelMax   = 1200.0;
/*
 * Battery Level
 */
const char   BatteryLevelStr[] = "Battery";
const char   BatteryLevelUM[]  = "Volts";
const float  BatteryLevelMin   = 0.0;
const float  BatteryLevelMax   = 26.0;

/*
 * Main Program
 */
// void setup()
// {
//   setupLCD();
// }

// void loop()
// {

//   LCD_Refresh(digitalRead(LCD_Button));

//   if ( 1 == 1 )      // example
//   {
//    delay(1000);
//    waterLevel++;
//    panelTemp++;
//    ambientTemp++;
//    batteryVoltage+=0.01;
//   }
// }
/*
 *
 */
void LCD_BackGround()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("___ \"C __ \"C ____ L");

  lcd.setCursor(0, 1);
  lcd.print("__.__ V   HH:mm  1/2");
}
/*
 *
 */
void setupLCD()
{

  pinMode(LCD_Button,INPUT);

  lcd.init();
  lcd.backlight();

  switch ( LCD_Mode )
  {
         case 1 :
                  LCD_BackGround();
                  break;
         case 2 :
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("Welcome OffGridBox");
                  break;
         default :
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("Check Variable");
                  lcd.setCursor(0,1);
                  lcd.print("LCD_MODE=1|2");
                  break;
  }
}
/*
 * Show All Values at a time
 */
void LCD_ShowAllValues()
{
  lcd.setCursor(0, 0);
  if(panelTemp < 0 || panelTemp > 999 ){
    lcd.print("???");
  }else{
    lcd.print((int)panelTemp);
  }

  lcd.setCursor(7, 0);
  if(ambientTemp < 0 || ambientTemp > 999 ){
    lcd.print("???");
  }else{
    lcd.print((int)ambientTemp);
  }

  lcd.setCursor(13, 0);
  if(waterLevel < 0 || waterLevel > 9999 ){
    lcd.print("????");
  }else{
    lcd.print((int)waterLevel);
  }

  lcd.setCursor(0, 1);
  if(batteryVoltage < 0 || batteryVoltage > 30 ){
    lcd.print("??");
  }else{
    lcd.print(batteryVoltage);
  }

  lcd.setCursor(10, 1);
  if(time_HH < 0 || time_HH > 24 ){
    lcd.print("??");
  }else{
    lcd.print(time_HH);
  }

  lcd.setCursor(13, 1);
  if(time_mm < 0 || time_mm > 59 ){
    lcd.print("??");
  }else{
    lcd.print(time_mm);
  }
}
/*
 * Show One Value at a time
 */
void LCD_ShowOneValue()
{
  lcd.clear();
  lcd.setCursor(0,0);

  switch (LCD_State)
  {
         case 1  :
                   LCD_Mode = 2;
                   lcd.print(PanelTempStr);

                   lcd.setCursor(0,1);
                   if ( panelTemp >= PanelTempMin && panelTemp <= PanelTempMax )
                     lcd.print((int)panelTemp);
                   else
                     lcd.print("ERROR!!!");

                   lcd.setCursor((21-sizeof(PanelTempUM)),1);
                   lcd.print(PanelTempUM);
                   break;
         case 2 :
                   LCD_Mode = 2;
                   lcd.print(AmbientTempStr);

                   lcd.setCursor(0,1);
                   if (ambientTemp >= AmbientTempMin && ambientTemp <= AmbientTempMax )
                      lcd.print((int)ambientTemp);
                   else
                     lcd.print("ERROR!!!");

                   lcd.setCursor((21-sizeof(AmbientTempUM)),1);
                   lcd.print(AmbientTempUM);
                   break;
         case 3  :
                   LCD_Mode = 2;
                   lcd.print(WaterLevelStr);

                   lcd.setCursor(0,1);
                   lcd.print((int)waterLevel);

                   lcd.setCursor((21-sizeof(WaterLevelUM)),1);
                   lcd.print(WaterLevelUM);
                   break;
         case 4  :
                   LCD_Mode = 2;
                   lcd.print(BatteryLevelStr);

                   lcd.setCursor(0,1);
                   lcd.print((int)batteryVoltage);

                   lcd.setCursor((21-sizeof(BatteryLevelUM)),1);
                   lcd.print(BatteryLevelUM);
                   break;
         case 5  :
                   LCD_ShowAllValues();
                   break;
         default :
                   lcd.print("CHECK LCD_STATE VALUE");
                   lcd.setCursor(0,1);
                   lcd.print((int)LCD_State);
                   break;
  }

}
/*
 * Update values on display
 */
void LCD_Refresh(boolean ChangeValue)
{
  if (ChangeValue)
  {
    LCD_State ++;

    if ( LCD_State > 5 )
      LCD_State = 1;
  }

  if ( LCD_State == 5 )
  {
   if (LCD_Mode != 1)
   {
     LCD_BackGround();
     LCD_Mode = 1;
   }

   LCD_ShowAllValues();
  }
  else {
        LCD_ShowOneValue();
       }
}

#endif
