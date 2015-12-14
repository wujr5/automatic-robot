/*
  modified 24-09-2015
  by jingtao
 */
int LED[] = {51, 53, 52, 50,
             47, 49, 48, 46,
             43, 45, 44, 42,
             39, 41, 40, 38,
             35, 37, 36, 34};
//int length = 4;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < 16; i++) {
    pinMode(LED[i], OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED[i], HIGH);
    delay(100);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED[i*4+3], HIGH);
    delay(100);
  }
  for (int i = 15; i >12; i--) {
    digitalWrite(LED[i], HIGH);
    delay(100);
  }
  for (int i = 3; i > 0; i--) {
    digitalWrite(LED[i*4], HIGH);
    delay(100);
  }
  for (int i = 5; i < 7; i++) {
    digitalWrite(LED[i], HIGH);
    delay(100);
  }
  for (int i = 10; i > 8; i--) {
    digitalWrite(LED[i], HIGH);
    delay(100);
  }
  for (int i = 0; i < 16; i++) {
    digitalWrite(LED[i], LOW);
    delay(200);
  }
//  digitalWrite(LED[1], OUTPUT);
}
