/*
============================================================
📌 Project Title
Arduino 4 Digit 7 Segment Animation (PLAY & STOP)
[COMMON ANODE VERSION]

📝 Description
Same animation as the common cathode version,
but adapted for common anode displays.

Logic inverted:
- Segment: LOW = ON
- Digit: HIGH = ON

Inspired by classic VCD player blinking style.
============================================================
*/

int seg[] = {2,3,4,5,6,7,8};
int digit[] = {9,10,11,12};

// COMMON ANODE (INVERTED DATA)
byte P[] = {0,0,1,1,0,0,0};
byte L[] = {1,1,1,0,0,0,1};
byte A[] = {0,0,0,1,0,0,0};
byte Y[] = {1,0,0,0,1,0,0};

byte S[] = {0,1,0,0,1,0,0};
byte T[] = {1,1,1,0,0,0,0};
byte O[] = {0,0,0,0,0,0,1};

byte OFF[] = {1,1,1,1,1,1,1};

// ======================
// SETUP
// ======================

void setup() {
  for(int i=0;i<7;i++) pinMode(seg[i], OUTPUT);
  for(int i=0;i<4;i++) pinMode(digit[i], OUTPUT);

  // Turn OFF all digits
  for(int i=0;i<4;i++) digitalWrite(digit[i], LOW);
}

// ======================
// DISPLAY CORE
// ======================

void displayDigit(byte data[], int d) {

  // 1. Turn OFF all digits
  for(int i=0;i<4;i++) digitalWrite(digit[i], LOW);

  // 2. Clear segment (HIGH = OFF)
  for(int i=0;i<7;i++) digitalWrite(seg[i], HIGH);

  delayMicroseconds(200);

  // 3. Set segment data
  for(int i=0;i<7;i++) digitalWrite(seg[i], data[i]);

  // 4. Turn ON selected digit
  digitalWrite(digit[d], HIGH);

  delay(2);
}

// ======================
// SHOW
// ======================

void show4(byte d1[], byte d2[], byte d3[], byte d4[], int duration){
  unsigned long start = millis();
  while(millis() - start < duration){
    displayDigit(d1,0);
    displayDigit(d2,1);
    displayDigit(d3,2);
    displayDigit(d4,3);
  }
}

// ======================
// CLEAR
// ======================

void clearDisplay(int duration){
  unsigned long start = millis();
  while(millis() - start < duration){
    
    for(int i=0;i<4;i++) digitalWrite(digit[i], LOW);
    for(int i=0;i<7;i++) digitalWrite(seg[i], HIGH);

    delay(2);
  }
}

// ======================
// BLINK
// ======================

void blinkPlay(){
  show4(OFF,OFF,OFF,OFF,1000);
  show4(P,L,A,Y,1000);
  show4(OFF,OFF,OFF,OFF,1000);
  show4(P,L,A,Y,1000);
  show4(OFF,OFF,OFF,OFF,1000);
  show4(P,L,A,Y,1000);
}

void blinkStop(){
  show4(OFF,OFF,OFF,OFF,1000);
  show4(S,T,O,P,1000);
  show4(OFF,OFF,OFF,OFF,1000);
  show4(S,T,O,P,1000);
}

// ======================
// ANIMATION
// ======================

void animPlay(){
  show4(OFF,OFF,OFF,P,1000);
  show4(OFF,OFF,P,L,1000);
  show4(OFF,P,L,A,1000);
  show4(P,L,A,Y,1000);

  blinkPlay();

  clearDisplay(200);
  delay(1000);
}

void animStop(){
  show4(OFF,OFF,OFF,S,1000);
  show4(OFF,OFF,S,T,1000);
  show4(OFF,S,T,O,1000);
  show4(S,T,O,P,1000);

  blinkStop();

  clearDisplay(200);
  delay(1000);
}

// ======================
// LOOP
// ======================

void loop() {

  animPlay();

  clearDisplay(200);
  clearDisplay(500);

  animStop();

  clearDisplay(200);
  clearDisplay(500);
}