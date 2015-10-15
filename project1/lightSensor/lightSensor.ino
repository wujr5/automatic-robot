void setup() {
  // put your setup code here, to run once:
  pinMode(21, INPUT);
  pinMode(20, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(50, OUTPUT);

  digitalWrite(20, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int light = digitalRead(21);
  if (light == 1) {
    digitalWrite(51, HIGH);
    digitalWrite(50, LOW);
  } else {
    digitalWrite(50, HIGH);
    digitalWrite(51, LOW);
  }
  
}
