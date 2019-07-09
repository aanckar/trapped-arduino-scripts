int INPUT_PORT_1 = 2;
int INPUT_PORT_2 = 4;
int INPUT_PORT_3 = 6;
int INPUT_PORT_4 = 8;
int INPUT_PORT_5 = 10;
int OUTPUT_PORT = 12;
int INPUT_ACTIVE_STATE = LOW;
int IS_COMPLETE = false;
int DEBUG = true;

void setup()
{
  pinMode(INPUT_PORT_1, INPUT_PULLUP);
  pinMode(INPUT_PORT_2, INPUT_PULLUP);
  pinMode(INPUT_PORT_3, INPUT_PULLUP);
  pinMode(INPUT_PORT_4, INPUT_PULLUP);
  pinMode(INPUT_PORT_5, INPUT_PULLUP);
  pinMode(OUTPUT_PORT, OUTPUT);
  digitalWrite(OUTPUT_PORT, LOW);
  Serial.begin(9600);
}

void loop()
{
  int VAL_1 = digitalRead(INPUT_PORT_1);
  int VAL_2 = digitalRead(INPUT_PORT_2);
  int VAL_3 = digitalRead(INPUT_PORT_3);
  int VAL_4 = digitalRead(INPUT_PORT_4);
  int VAL_5 = digitalRead(INPUT_PORT_5);

  if (DEBUG)
  {
    if (!VAL_1)
    {
      Serial.println("Input 1");
    }
    if (!VAL_2)
    {
      Serial.println("Input 2");
    }
    if (!VAL_3)
    {
      Serial.println("Input 3");
    }
    if (!VAL_4)
    {
      Serial.println("Input 4");
    }
    if (!VAL_5)
    {
      Serial.println("Input 5");
    }
  }

  if (
      VAL_1 == INPUT_ACTIVE_STATE &&
      VAL_2 == INPUT_ACTIVE_STATE &&
      VAL_3 == INPUT_ACTIVE_STATE &&
      VAL_4 == INPUT_ACTIVE_STATE &&
      VAL_5 == INPUT_ACTIVE_STATE)
  {
    IS_COMPLETE = true;
  }

  if (IS_COMPLETE)
  {
    digitalWrite(OUTPUT_PORT, HIGH);
  }
}