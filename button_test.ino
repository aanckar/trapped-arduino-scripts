/*
 * BUTTON TEST
 * 
 * Push the button. A message is printed in the serial monitor.
 * Your mind = blown
 *   
 * by Trapped Room Escape
 */

const int LED = 13;
const int BUTTON = 7;

int val = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);  
}

void loop() {
  val = digitalRead(BUTTON);
  if ( val == 1 ) {
    digitalWrite(LED, HIGH);
    Serial.print("LOL");
  }
}
