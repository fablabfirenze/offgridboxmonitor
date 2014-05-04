#ifndef LCD_OffGridBox
#define LCD_OffGridBox

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// SPI address tested   = 0x3F
LiquidCrystal_I2C lcd(LCD_ADDR,LCD_NCAR,LCD_NROW);

/*
 *
 * Tested Pin Configuration
 *
 * 4     Push button to change value on display
 * 20,21 LCD Display
 *
 */
/*
 * Binding Structure
 */
struct LCD_Values {
                    // One Value at a time
                    int       State;        // State of LCD. Last record must be -1!!!
                    float    *Value;        // Variable address (must be the address!!!)
                    float     Min;          // Min Value
                    float     Max;          // Max Value
                    int       NDec;         // #decimal
                    String    Label;        // Value's Label
                    String    UM;           // Unity of measure
                    // All values at a time
                    String    ShortLabel;
                    int       Row;          // -1 don't show
                    int       Col;          //
                    int       Page_Num;     // Display value on Page Num (must start from 1 and must be consequentially!!!)
};
int LCD_State;                  // Current state
#define LCD_State_Start  -1;    // -1 = All Values at a time

LCD_Values  LCD_A_Val[] = { 1, &panelTemp,         0.0,    130.0, 0, "Panel Temp.",     "\"C",    " PT",   0,  0, 1,
                            2, &ambientTemp,       0.0,     80.0, 0, "Ambient Temp.",    "\"C",    " AT",   0,  7, 1,
                            3, &batteryVoltage,    0.0,     99.0, 1, "Battery Voltage", "V",      " BV",   0, 12, 1,
                            4, &batteryPercentage, 0.0,    999.0, 0, "Battery %",       "%",      " B%",   1,  0, 1,
                            5, &waterLevel,        0.0,   8500.0, 0, "Water Level",     "l",      " WL",   1, 11, 1,
                            6, &powerProd,         0.0,    150.0, 1, "Energy Produced",  "kWh",      " kWh+",   0,  0, 2,
                            7, &powerUsed,         0.0,    150.0, 1, "Energy Used",      "kWh",      " kWh-",   1,  0, 2,
                           -1, 0x00,               0.0,      0.0, 0, 0x00,              0x00,      0x00,  -1,  0, 0  };

// Welcome Message
String LCD_Welcome = "Feat. by \"La Fabbrica del Sole\", \"FabLab Firenze\", \"OXFAM Italia\", \"Impact HUB Firenze\" ";

// BOUNCE THE BUTTON
int LCD_BOLD_VAL;
int LCD_BNEW_VAL;

// Function declaration
boolean CHECK_LCD_DIM();
/*
 *
 */
void setupLCD()
{

  pinMode(LCD_Button,INPUT);

  lcd.init();
  LCD_ON();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome OffGridBox");
  LCD_Scroll_Text(1,LCD_Welcome);
  lcd.clear();

  LCD_CurrPage = 1;
  LCD_ON();
  LCD_State = LCD_State_Start;
}
/*
 * Show All Values at a time
 */
void LCD_ShowAllValues()
{

  int idx0;
  int idx1;
  float Value;
  int   MaxDigit;
  int   ValDigit;
  int   LastPage;
  String OverFlow = "?????????????";
  String Fill     = "             ";

  LastPage = 0;

  for ( idx0 = 0; LCD_A_Val[idx0].State != -1; idx0++)
  {
    if (LCD_A_Val[idx0].Row >= 0 && LCD_A_Val[idx0].Page_Num == LCD_CurrPage)
    {
      lcd.setCursor(LCD_A_Val[idx0].Col, LCD_A_Val[idx0].Row);

      // number of digit
      Value = LCD_A_Val[idx0].Max;
      for ( MaxDigit = 1; Value; MaxDigit++)
         Value = (int) Value / 10;

      if ( *LCD_A_Val[idx0].Value >= LCD_A_Val[idx0].Min && *LCD_A_Val[idx0].Value <= LCD_A_Val[idx0].Max )
      {
         // number of digit
         Value = *LCD_A_Val[idx0].Value;
         for ( ValDigit = 1; Value; ValDigit++)
             Value = (int) Value / 10;

         if (MaxDigit > ValDigit)
           lcd.print(Fill.substring(0,MaxDigit - ValDigit ));

         lcd.print(*LCD_A_Val[idx0].Value, LCD_A_Val[idx0].NDec );
      }
      else {
            MaxDigit += LCD_A_Val[idx0].NDec + (LCD_A_Val[idx0].NDec > 0);

            lcd.print(OverFlow.substring(1,MaxDigit));
           }

      lcd.print(LCD_A_Val[idx0].ShortLabel);
    }
    if ( LCD_A_Val[idx0].Page_Num > LastPage )
    {
      LastPage = LCD_A_Val[idx0].Page_Num;
    }
  }

  if ( ( millis() - LCD_CurrPageTime ) > LCD_Page_Time )
  {
    lcd.clear();
    if ( LastPage == LCD_CurrPage )
      LCD_CurrPage = 1;
    else
         LCD_CurrPage++;

    LCD_CurrPageTime = millis();
  }

}
/*
 * Show One Value at a time
 */
void LCD_ShowOneValue()
{
  int idx0;
  int idx1;
  float Value;
  int   MaxDigit;
  int   ValDigit;
  String Fill     = "             ";
  String OverFlow = "?????????????";

  for ( idx0 = 0; LCD_A_Val[idx0].State != -1; idx0++)
  {
    if (LCD_A_Val[idx0].State == LCD_State)
    {
       break;
    }
  }

  if (LCD_A_Val[idx0].State != LCD_State)
  {
    lcd.setCursor(0,0);
    lcd.print("Program Error");
    lcd.setCursor(0,1);
    lcd.print("LCD_ShowOneValue.1 ");
    lcd.print(idx0);
    return;
  }

  lcd.setCursor(0,0);

  lcd.print(LCD_A_Val[idx0].Label);
  lcd.setCursor(0,1);

  if ( *LCD_A_Val[idx0].Value >= LCD_A_Val[idx0].Min && *LCD_A_Val[idx0].Value <= LCD_A_Val[idx0].Max )
  {

    // number of digit
      Value = LCD_A_Val[idx0].Max;
      for ( MaxDigit = 1; Value; MaxDigit++)
         Value = (int) Value / 10;

    // number of digit
      Value = *LCD_A_Val[idx0].Value;
      for ( ValDigit = 1; Value; ValDigit++)
         Value = (int) Value / 10;

    if ( MaxDigit > ValDigit )
      lcd.print(Fill.substring(0,MaxDigit - ValDigit ));

    if ( LCD_A_Val[idx0].NDec == 0 )
      lcd.print((int)*LCD_A_Val[idx0].Value);
    else
      lcd.print(*LCD_A_Val[idx0].Value, LCD_A_Val[idx0].NDec );
  } else {
           // number of digit
          Value = LCD_A_Val[idx0].Max;
          for ( MaxDigit = 1; Value; MaxDigit++)
             Value = (int) Value / 10;

          lcd.print(OverFlow.substring(1,MaxDigit));
         }

  lcd.setCursor((20-LCD_A_Val[idx0].UM.length()),1);
  lcd.print(LCD_A_Val[idx0].UM);

}
/*
 * Update values on display
 * Entry point from main loop
 */
void LCD_Refresh(boolean ChangeValue)
{
  int new_state = -1;
  int idx0      = -1;

//  lcd.setCursor(0,2);
//  lcd.print(ChangeValue);

  if (ChangeValue)
  {
    LCD_ON();

    new_state = LCD_State + 1;

    if (new_state <= 0 )
      new_state = 1;

    LCD_State = -1;
    for ( idx0 = 0; LCD_A_Val[idx0].State != -1; idx0++)
    {
      if (LCD_A_Val[idx0].State == new_state)
      {
         LCD_State = LCD_A_Val[idx0].State;
         break;
      }
    }

    lcd.clear();
    // if LCD_State = -1 then show all value at a time

  } else {
           if (CHECK_LCD_DIM())
             return;
  }

  if ( LCD_State == -1 )
    LCD_ShowAllValues();
  else
    LCD_ShowOneValue();

}
/*
 * Read Button State
 */

boolean Read_LCD_Button()
{
  LCD_BNEW_VAL = digitalRead(LCD_Button);

  if (LCD_BNEW_VAL != LCD_BOLD_VAL )
  {
    LCD_BOLD_VAL = LCD_BNEW_VAL;
    return (LCD_BNEW_VAL == HIGH);
  }
  else {
         return false;
  }
}
/*
 *
 */
void LCD_Scroll_Text(int Row, String LCD_Welcome)
{
  int idx0;
  int idx1 = LCD_Welcome.length();

  for ( idx0 = 0; idx0 < idx1; idx0++)
  {
     lcd.setCursor(0,Row);
     lcd.print(LCD_Welcome.substring(idx0,idx0+19));
     delay(300);
     if ( Read_LCD_Button() )
       break;
  }
}
/*
 * Turn ON LCD Backligth
 */
void LCD_ON()
{
  lcd.display();
  lcd.backlight();

  LCD_TIME_ON = millis();
}
/*
 * Check if turn-off LCD
 */
boolean  CHECK_LCD_DIM()
{

//  lcd.setCursor(0,3);
//  lcd.print(( millis() - LCD_TIME_ON));
//  lcd.print(" ");
//  lcd.print(LCD_DIM);

  if ( (long)( millis() - LCD_TIME_ON ) > LCD_DIM )
  {
    lcd.noDisplay();
    lcd.noBacklight();
    return true;
  } else {
           return false;
  }
}
#endif
