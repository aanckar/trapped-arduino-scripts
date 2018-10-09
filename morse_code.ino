/*
 * MORSE CODE PLAYER
 * 
 * Plays morse code message on speaker and LED
 *   
 * by Trapped Room Escape
 */

// Speaker & LED pin
const int SPEAKER = 8;
const int LED = 13;

// Morse code: 1 = short, 2 = long
// The code is 8735
const int CODE[4][5] = {
  {2,2,2,1,1},
  {2,2,1,1,1},
  {1,1,1,2,2},
  {1,1,1,1,1}
};

/*
 * Don't edit below this
 */
// Timeouts (in milliseconds)
const int SHORT = 400;
const int LONG = 1150;
const int PAUSE = 350;
// Tone (in Hertz)
const int TONE = 880;

void setup() {
  Serial.begin(9600);
  digitalWrite(LED, LOW); 
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  int i;
  int j;
  for ( i=0; i<4; i++ ) {
    for ( j=0; j<5; j++ ) {
      if ( CODE[i][j] == 1 ) {
        playShort();
      } else if ( CODE[i][j] == 2 ) {
        playLong();
      }
    }
    playPause();
  }
  playLongPause();
}

void playShort() {
  Serial.print(".");
  digitalWrite(LED, HIGH); 
  tone(SPEAKER, TONE, SHORT);
  delay(SHORT);
  digitalWrite(LED, LOW); 
  delay(PAUSE);
}

void playLong() {
  Serial.print("-");
  digitalWrite(LED, HIGH); 
  tone(SPEAKER, TONE, LONG);
  delay(LONG);
  digitalWrite(LED, LOW);
  delay(PAUSE);
}

void playPause() {
  Serial.println("");
  digitalWrite(LED, LOW); 
  delay(4 * PAUSE);
}

void playLongPause() {
  Serial.println("");
  digitalWrite(LED, LOW); 
  delay(12 * PAUSE);
}
