
#include <GSM.h>


#define PINNUMBER "4660"
#define PHONENUMBER "3938916804"

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;


/*
 * GSM init
 */
void setupGSM()
{
  
  Serial.print("Initializing GSM card...");
  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("GSM initialized");
  
}


void sendSms(String dataString) {
  // send the message
  sms.beginSMS(PHONENUMBER);
  sms.print(dataString);
  sms.endSMS(); 
  Serial.println("\nCOMPLETE!\n");
}