/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led1 = 3;
int led2 = 4;
int led3 = 5;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);    
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led1, LOW); // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led1, HIGH);  // turn the LED off by making the voltage LOW
  delay(100); 
  digitalWrite(led2, LOW); // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led2, HIGH);  // turn the LED off by making the voltage LOW
  delay(100); 
  digitalWrite(led3, LOW); // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led3, HIGH);  // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}
