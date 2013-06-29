#include <VirtualWire.h>

int switchPin = A5;

void setup()
{
  Serial.begin(9600);	  // Debugging only
  Serial.println("setup");

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_set_tx_pin(6); 
      
  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);
}

void loop()
{
  char *msg;
  
  if(digitalRead(A5) == LOW){
    Serial.print("BUTTON PRESSED");
    char *msg = "test"; // max 26 characters
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg) + 1); // +1 to include null byte
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
  }
}
  
