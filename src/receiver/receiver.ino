#include <VirtualWire.h>

void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_set_rx_pin(2);
  vw_rx_start();       // Start the receiver PLL running

  pinMode(8, OUTPUT);
}

void loop()
{
  
  digitalWrite(8, LOW);
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    // Message with a good checksum received, dump it.
    Serial.print("Got: ");
    Serial.print((char*)buf);
    
    if(memcmp(buf, "test", 4) == 0){
      digitalWrite(8, HIGH);  
    }

    Serial.println("");
 }
}
