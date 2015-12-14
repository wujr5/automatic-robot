
int LED[] = {51, 53, 52, 50,
             47, 49, 48, 46,
             43, 45, 44, 42,
             39, 41, 40, 38,
             35, 37, 36, 34};
int length = 4;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  for (int i = 0; i < 16; i++) {
    pinMode(LED[i], OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 0; i < 16; i++) {
    digitalWrite(LED[i], HIGH);
    delay(1000);
  }
//  digitalWrite(LED[1], OUTPUT);
}
