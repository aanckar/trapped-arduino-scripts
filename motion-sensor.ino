int LED = 13;
int ECHOPIN = 2;
int TRIGPIN = 3;
int OUT = 4;

void setup()
{
   pinMode(LED, OUTPUT);
   pinMode(ECHOPIN, INPUT);
   pinMode(TRIGPIN, OUTPUT);
   pinMode(OUT, OUTPUT);
   Serial.begin(9600);
}

void loop()
{
   checkSonic();
}

void checkSonic()
{
   // Set the trigger pin to low for 2uS
   digitalWrite(TRIGPIN, LOW);
   delayMicroseconds(2);
   // Send a 10uS high to trigger ranging
   digitalWrite(TRIGPIN, HIGH);
   delayMicroseconds(10);
   // Send pin low again
   digitalWrite(TRIGPIN, LOW);
   // Read in times pulse
   int distance = pulseIn(ECHOPIN, HIGH);
   // Calculate distance from time of pulse
   distance = distance / 58;
   Serial.println(distance);
   if (distance <= 10 && distance > 0)
   {
     Serial.println("motion detected");
     digitalWrite(OUT, 1);
     digitalWrite(LED, 1);
   } else {
     Serial.println("no motion detected");
     digitalWrite(OUT, 0);
     digitalWrite(LED, 0);
   }
   delay(200);
}