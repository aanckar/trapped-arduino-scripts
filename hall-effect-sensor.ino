int HALL_SENSOR_1_INPUT = 2;
int HALL_SENSOR_1_OUTPUT = 13;

void setup()
{
  pinMode(HALL_SENSOR_1_OUTPUT, OUTPUT);
  pinMode(HALL_SENSOR_1_INPUT, INPUT);
}

void loop()
{
  int state = digitalRead(HALL_SENSOR_1_INPUT);
  if (state == LOW)
  {
    digitalWrite(HALL_SENSOR_1_OUTPUT, HIGH);
  }
  else
  {
    digitalWrite(HALL_SENSOR_1_OUTPUT, LOW);
  }
}