/*
 * BUTTON SEQUENCE PUZZLE
 * 
 * Push buttons in the correct order to:
 *  - Turn on LED
 *  - Play a melody on speaker
 *  - Open a magnetic lock
 *   
 * by Trapped Room Escape
 */

// LED and speaker pins
const int LOCK = 9;
const int LED = 13;
const int SPEAKER = 3;

// Enter number of buttons and their pins here
const int BUTTONS[5] = {4,5,6,7,8};

// Enter correct sequence length and button pins
const int SEQUENCE[5] = {6,8,7,4,5};

/*
 * Don't edit below this
 */
const int PRESSED_STATE = LOW;
const int BUTTONS_LENGTH = sizeof(BUTTONS)/sizeof(BUTTONS[0]);
const int SEQUENCE_LENGTH = sizeof(SEQUENCE)/sizeof(SEQUENCE[0]);
bool complete = false;
int lastPressedButton;
int input[SEQUENCE_LENGTH];
int counter;

void setup() {
  // Init serial (for testing)
  Serial.begin(9600);
  // Init outputs: Lock, LED and speaker
  pinMode(LOCK, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
  // Init button pins (with internal pull-up resistors enabled)
  int i;
  for ( i=0; i<BUTTONS_LENGTH; i++ ) {
    pinMode(BUTTONS[i], INPUT_PULLUP);
  }
  // Actiavte lock on startup
  digitalWrite(LOCK, HIGH); 
}

void loop() {
  // Once puzzle is completed, do nothing
  if ( !complete ) {
    
    // Allow input (0-9) thru serial monitor for testing
    int serialInput;
    if ( Serial.available() > 0 ) { 
      serialInput = Serial.read();
      if ( serialInput >= '0' && serialInput <= '9' ) {
        serialInput = serialInput - 48;
      }
    }

    // Check if a button was pressed
    int pressedButton = -1;
    int i;
    for ( i=0; i<BUTTONS_LENGTH; i++ ) {
      if ( digitalRead(BUTTONS[i]) == PRESSED_STATE || serialInput == BUTTONS[i] ) {
        // Consecutive presses of the same button are ignored
        if ( lastPressedButton != BUTTONS[i] ) {
          lastPressedButton = BUTTONS[i];
          pressedButton = BUTTONS[i];
        }
      }
    }

    // Only do stuff if a button press was detected
    if ( pressedButton > -1 ) {
      int correct = 0;
      int i;
      // Create input array of button press history
      // Also check if entries match the correct sequence
      for ( i=0; i<SEQUENCE_LENGTH-1; i++ ) {
        // Push entries left and check them
        input[i] = input[i+1];
        if ( input[i] == SEQUENCE[i] ) { correct++; }
      }
      // Insert current entry at end of array and check it
      input[SEQUENCE_LENGTH-1] = pressedButton;
      if ( input[SEQUENCE_LENGTH-1] == SEQUENCE[SEQUENCE_LENGTH-1] ) { correct++; }

      // Print stuff to serial
      Serial.print("Input history: ");
      for ( i = 0; i < SEQUENCE_LENGTH; i++ ) {
         Serial.print(input[i], DEC);
      }
      Serial.println();

      // If all entries are correct
      if ( correct == SEQUENCE_LENGTH ) {
        // Print success message to serial
        Serial.println();
        Serial.println("CODE CORRECT!");
        Serial.println();
        // Reset correct counter and trigger completion
        correct = 0;
        complete = true;
        success();
      } 
      // If sequence isn't correct, make sure LED is off
      else {
        digitalWrite(LED, LOW);
      }

      // Increment button press counter
      counter++;
    }
  }
}

void success() {
  digitalWrite(LED, HIGH);
  playSound();
  openLock();
  delay(4000);
  digitalWrite(LED, LOW);
}

void playSound() {
  Serial.println("Play sound");
  const int TIME = 150;
  tone(SPEAKER, 880, TIME);
  delay(TIME);
  tone(SPEAKER, 1109, TIME);
  delay(TIME);
  tone(SPEAKER, 1319, TIME);
  delay(TIME);
  tone(SPEAKER, 1760, 2*TIME);
  delay(2*TIME);
  tone(SPEAKER, 1661, TIME);
  delay(TIME);
  tone(SPEAKER, 1760, 4*TIME);
}

void openLock() {
  Serial.println("Open lock");
  digitalWrite(LOCK, LOW);
}