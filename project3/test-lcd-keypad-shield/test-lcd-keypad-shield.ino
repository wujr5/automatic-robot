void setup() {
  // put your setup code here, to run once:
//  pinMode(6, OUTPUT);
  for (int i = 14; i <= 21; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:\
  for (int i = 14; i <= 21; i++) {
    digitalWrite(i, HIGH);
  }
}
