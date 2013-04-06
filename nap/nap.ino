#include <Event.h>
#include <Timer.h>

/*
* It's nap time
*/

int redPin = 9;
int bluePin = 10;
int greenPin = 11;
int buzzPin = 5;
int i = 0;
int UP = 1;
int wakeUpIn = 10 * 1000; // 10 minutes
int buzzFor = 2 * 1000; // 2 seconds
int buzzEvent;
int ledEvent;
int switchPin = A5;
int switchValue;

Timer t;

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(switchPin, INPUT);
  
  digitalWrite(switchPin, HIGH); //pull-up

  ledEvent = t.every(10, updateColor);
  
  t.after(wakeUpIn, buzz);
}

void loop()
{
  t.update();

  switchValue = digitalRead(switchPin);
  if (!switchValue == HIGH && buzzEvent) {
    wakeUp();
  }
}

void wakeUp ()
{
  // stop the buzz
  t.stop(buzzEvent); 
  digitalWrite(buzzPin, LOW);
  
  // flash twice
  t.stop(ledEvent);
  color(0, 0, 0);
  delay(100);
  color(0, 255, 0);
  delay(100);
  color(0, 0, 0);
  delay(100);
  color(0, 255, 0);
  delay(100);
  color(0, 0, 0);
  delay(100);
}

void buzz ()
{
  buzzEvent = t.oscillate(buzzPin, buzzFor, HIGH);
}

void updateColor ()
{
  if (UP && i >= 255) {
    UP = 0;
  } else if (!UP && i <= 0) {
    UP = 1;
  }

  if (UP) {
    i += 1;
  } else {
    i -= 1;
  }

  color(0, i, 0);
}

void color (unsigned char red, unsigned char green, unsigned char blue)	//the color generating function
{
   analogWrite(redPin, 255-red);
   analogWrite(bluePin, 255-blue);
   analogWrite(greenPin, 255-green);
}
